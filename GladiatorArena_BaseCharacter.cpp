// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Victory/Weapons/MeleeWeapon.h"
#include "Victory/Controllers/BasePlayerController.h"
#include "Animation/AnimInstance.h"
#include "Components/SphereComponent.h"
#include "Victory/GameModes/SurvivalGameMode.h"
#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollision->SetupAttachment(RootComponent);


}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(MeleeWeaponClass != nullptr)
	{
		MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(MeleeWeaponClass);
		MeleeWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightMeleeWeaponSocket"));
		MeleeWeapon->SetOwner(this);
	}


	Health = MaxHealth;
	Stamina = MaxStamina;
}

float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) 
{
	if(!bIsBlocking)
	{
		float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		DamageToApply = FMath::Min(Health, DamageToApply);

		Health -= DamageToApply;

		if(Health > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("HEALTH = %f"), Health);
		}

		if(Health <= 0)
		{
			if(IsPlayerControlled())
			{
				ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());

				if(PlayerController != nullptr)
				{
					PlayerController->DisplaySurvivalGameModeScreen(2);
				}

				bIsMovementDisabled = true;

				PlayerController->Restart();
			}
			else
			{
				ASurvivalGameMode* SurvivalGameMode = GetWorld()->GetAuthGameMode<ASurvivalGameMode>();

				if(SurvivalGameMode != nullptr)
				{
					SurvivalGameMode->EnemyDefeated();
				}

				if(MeleeWeapon != nullptr)
				{
					MeleeWeapon->Destroy();
				}

				Destroy();
			}
		}

		return DamageToApply;
	}

	return 0;
}


void ABaseCharacter::MoveForward(float Value) 
{
	if(Controller != nullptr && Value != 0.0f && !bIsMovementDisabled)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);

		if(Value > 0)
		{
			DodgeIndex = 0;
		}
		else
		{
			DodgeIndex = 1;
		}
	}
}

void ABaseCharacter::MoveRight(float Value) 
{
	if(Controller != nullptr && Value != 0.0f && !bIsMovementDisabled)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);

		if(Value > 0)
		{
			DodgeIndex = 2;
		}
		else
		{
			DodgeIndex = 3;
		}
	}
}

void ABaseCharacter::TurnRate(float Value) 
{
	TurnValue = Value;
}

void ABaseCharacter::DisableMovement(bool Active) 
{
	bIsMovementDisabled = Active;
}

void ABaseCharacter::BlockInitiated() 
{
	if(Stamina >= BlockStaminaCost && !bIsAttacking)
	{
		bIsMovementDisabled = true;
		bIsBlocking = true;
		GetWorld()->GetTimerManager().SetTimer(BlockingTimerHandle, this, &ABaseCharacter::BlockCancelled, BlockingMaxTime, false);
	}
	else if(Stamina < BlockStaminaCost)
	{

		ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());

		if(PlayerController != nullptr)
		{
			PlayerController->StaminaLow();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CAST FAILED"));
		}
	}
}

void ABaseCharacter::BlockCancelled() 
{
	if(bIsBlocking)
	{
		bIsMovementDisabled = false;
		Stamina -= BlockStaminaCost;

		if(GetWorld()->GetTimerManager().IsTimerActive(BlockingTimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(BlockingTimerHandle);
		}

		bIsBlocking = false;
	}
	
	
}

void ABaseCharacter::Dodge() 
{
	if(!bIsDodging && Stamina >= DodgeStaminaCost)
	{
		if(DodgeIndex == 0)
		{
			PlayAnimMontage(ForwardDodge, 1);
		}

		if(DodgeIndex == 1)
		{
			PlayAnimMontage(BackwardDodge, 1);
		}

		if(DodgeIndex == 2)
		{
			PlayAnimMontage(RightDodge, 1);
		}

		if(DodgeIndex == 3)
		{
			PlayAnimMontage(LeftDodge, 1);
		}

		bIsDodging = true;
		Stamina -= DodgeStaminaCost;
	}
	else if(Stamina < DodgeStaminaCost)
	{
		ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());

		if(PlayerController != nullptr)
		{
			PlayerController->StaminaLow();
		}
	}
}

void ABaseCharacter::AttackComplete() 
{
	if(MeleeWeapon != nullptr)
	{
		MeleeWeapon->AttackFinished();
	}
}

float ABaseCharacter::HealthPercent() 
{
	return Health / MaxHealth;
}

float ABaseCharacter::StaminaPercent() 
{
	return Stamina / MaxStamina;
}
