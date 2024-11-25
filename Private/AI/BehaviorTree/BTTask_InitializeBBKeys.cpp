// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_InitializeBBKeys.h"

#include "AI/VirusAI.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_InitializeBBKeys::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, FVector::ZeroVector);
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISMOVETOFAIL, false);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISHOME, false);

    return Super::ExecuteTask(OwnerComp, NodeMemory);
}
