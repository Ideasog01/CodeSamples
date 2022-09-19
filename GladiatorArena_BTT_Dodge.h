#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Dodge.generated.h"

/**
 * 
 */
UCLASS()
class VICTORY_API UBTT_Dodge : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTT_Dodge();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
