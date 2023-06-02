#include "Encrypted/AI/BaseAIController.h"
#include "Encrypted/Enemy/EnemyClass.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Encrypted/Enemy/CameraEnemy.h"
#include "Encrypted/Enemy/DroneEnemy.h"
#include "Kismet/GameplayStatics.h"

ABaseAIController::ABaseAIController()
{
	//Initialise Blackboard & BehaviorTree & Drone (Owner)

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	//Initialise Blackboard Keys

	PlayerKey = "Target";

}

void ABaseAIController::SetPlayerCaught(APawn* InPawn)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsObject(PlayerKey, InPawn);
	}

	UE_LOG(LogTemp, Warning, TEXT("Target Set"));
}

void ABaseAIController::DisableEnemy(float Duration)
{
	if (Duration != 0)
	{
		GetWorldTimerManager().SetTimer(DisableTimer, this, &ABaseAIController::EnableEnemy, Duration, false, Duration);
	}

	bIsEnemyDisabled = true;

	ACameraEnemy* Camera = Cast<ACameraEnemy>(GetPawn());

	if (Camera)
	{
		Camera->DisableCameraRotation(false);
		Camera->EnableEnemyDisplay(true);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Camera Deactivated"));
	}

	ADroneEnemy* Drone = Cast<ADroneEnemy>(GetPawn());

	if (Drone)
	{
		Drone->DisableMovement(true);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Drone Deactivated"));
	}
}

void ABaseAIController::EnableEnemy()
{
	bIsEnemyDisabled = false;

	ACameraEnemy* Camera = Cast<ACameraEnemy>(GetPawn());

	if (Camera)
	{
		Camera->DisableCameraRotation(true);
		Camera->EnableEnemyDisplay(false);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Camera Activated"));
	}

	ADroneEnemy* Drone = Cast<ADroneEnemy>(GetPawn());

	if (Drone)
	{
		Drone->DisableMovement(false);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Drone Activated"));
	}
}

FTimerHandle ABaseAIController::GetDisableTimer()
{
	return DisableTimer;
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		if (BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
		}

		//Populate Patrol Locations

		BehaviorTreeComponent->StartTree(*BehaviorTree);

		UE_LOG(LogTemp, Warning, TEXT("Tree Started!"));

		GetWorldTimerManager().ClearTimer(DisableTimer);
	}
}
