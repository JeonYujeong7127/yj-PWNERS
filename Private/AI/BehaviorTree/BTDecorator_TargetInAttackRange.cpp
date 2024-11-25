// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTDecorator_TargetInAttackRange.h"

#include "AIController.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "AI/VirusAI.h"
#include "BehaviorTree/BlackboardComponent.h"

class AVirusAIBase;

bool UBTDecorator_TargetInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                  uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    AVirusAIBase* AIPawn = Cast<AVirusAIBase>(ControllingPawn);

    if (nullptr == ControllingPawn)
    {
        return false;
    }

    if (nullptr == AIPawn)
    {
        return false;
    }

    APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
    if (nullptr == Target)
    {
        return false;
    }

    float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
    float AttackRangeWithRadius = AIPawn->GetAttackRange();
    bResult = (DistanceToTarget <= AttackRangeWithRadius);

    UE_LOG(LogTemp, Log, TEXT("DistanceToTarget: %f, AttackRange: %f, bResult: %s"), DistanceToTarget, AttackRangeWithRadius, bResult ? TEXT("True") : TEXT("False"));

    return bResult;
}
