#pragma once

#include "CoreMinimal.h"
#include "AIController.h"


class UGameplayStatics;
class AEnemyClass;
class UBlackboardComponent;
class UBehaviorTreeComponent;
class ACameraEnemy;
class ADroneEnemy;

#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class ENCRYPTED_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABaseAIController();

	void SetPlayerCaught(APawn* InPawn);

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable)
	void DisableEnemy(float Duration);

	UFUNCTION(BlueprintCallable)
	void EnableEnemy();

	UFUNCTION(BlueprintCallable)
	FTimerHandle GetDisableTimer();

private:

	UBehaviorTreeComponent* BehaviorTreeComponent;

	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PlayerKey;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "AI")
	bool bIsEnemyDisabled;

	void OnPossess(APawn* InPawn) override;

	FTimerHandle DisableTimer;
	
};
