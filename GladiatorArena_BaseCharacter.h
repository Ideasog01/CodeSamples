#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Victory/Weapons/MeleeWeapon.h"
#include "Animation/AnimInstance.h"
#include "Components/SphereComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class VICTORY_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

public:

	ABaseCharacter();

protected:

	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnRate(float Value);

	void BlockInitiated();

	void BlockCancelled();

	void Dodge();

	UFUNCTION(BlueprintCallable)
	void AttackComplete();

	UFUNCTION(BlueprintCallable)
	void DisableMovement(bool Active);

	UFUNCTION(BlueprintCallable)
	float HealthPercent();

	UFUNCTION(BlueprintCallable)
	float StaminaPercent();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TurnValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BlockingMaxTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	float Health = 100;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	float MaxStamina = 100;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	float Stamina = 100;

	UPROPERTY(EditAnywhere, Category = Combat)
	float BlockStaminaCost = 10;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DodgeStaminaCost = 10;

	UPROPERTY(EditAnywhere, Category = Combat)
	float StaminaIncreaseRate = 1.2f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float RadiusDamage = 40;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int DodgeIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsMovementDisabled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsBlocking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	bool bIsDodging = false;


	UPROPERTY(EditAnywhere)
	TSubclassOf<AMeleeWeapon> MeleeWeaponClass;

	AMeleeWeapon* MeleeWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* ForwardDodge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* BackwardDodge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* RightDodge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* LeftDodge;

private:

	FTimerHandle BlockingTimerHandle;
};
