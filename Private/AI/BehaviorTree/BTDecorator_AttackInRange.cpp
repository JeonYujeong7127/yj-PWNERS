// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTDecorator_AttackInRange.h"
#include "AIController.h"
#include "AI/VirusAI.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "BehaviorTree/BlackboardComponent.h"

class AVirusAIBase;

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
    NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    AVirusAIBase* AIPawn = Cast<AVirusAIBase>(ControllingPawn);
    
    if(AIPawn->bIsPlayerInAttackRange)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGETINATTACKRANGE, AIPawn->TargetPlayerInAttackRange);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGETINATTACKRANGE, nullptr);
    }

    return AIPawn->bIsPlayerInAttackRange;
}
