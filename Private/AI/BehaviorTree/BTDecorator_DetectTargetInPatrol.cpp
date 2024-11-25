// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTDecorator_DetectTargetInPatrol.h"

#include "AIController.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "AI/AIController/AggressiveAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/VirusAI.h"

class AAggressiveAIController;
class AVirusAIBase;

bool UBTDecorator_DetectTargetInPatrol::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                   uint8* NodeMemory) const
{
    bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    AVirusAIBase* ControllingPawn = Cast<AVirusAIBase>(OwnerComp.GetAIOwner()->GetPawn());
    AAggressiveAIController* Controller = Cast<AAggressiveAIController>(ControllingPawn->GetController());
    for(auto PlayerInMesh : Controller->PlayersInNavMesh)
    {
        if(PlayerInMesh == OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET))
        {
            return true;
        }
    }
    
    return false;
}
