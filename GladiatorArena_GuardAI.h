#pragma once

#include "CoreMinimal.h"
#include "Victory/Characters/BaseCharacter.h"
#include "GuardAI.generated.h"

/**
 * 
 */
UCLASS()
class VICTORY_API AGuardAI : public ABaseCharacter
{
	GENERATED_BODY()

public:

	void SetGuardLevel(int Level);

	void GuardMeleeAttack();

	int GetLevel();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* GuardAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyProperties)
	int EnemyLevel;
	
};
