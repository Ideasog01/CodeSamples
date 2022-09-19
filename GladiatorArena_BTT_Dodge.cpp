#include "Victory/Characters/BaseCharacter.h"
#include "AIController.h"
#include "Victory/AI/BTT_Dodge.h"


UBTT_Dodge::UBTT_Dodge() 
{
    NodeName = TEXT("Dodge");
}

EBTNodeResult::Type UBTT_Dodge::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    ABaseCharacter* AICharacter = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if(AICharacter == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("FAILED GET CHARACTER"));
        return EBTNodeResult::Failed;
    }

    AICharacter->DodgeIndex = FMath::RandRange(1, 3);
    AICharacter->Dodge();

    return EBTNodeResult::Succeeded;
}
