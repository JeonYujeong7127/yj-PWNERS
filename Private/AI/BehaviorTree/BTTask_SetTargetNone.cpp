// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_SetTargetNone.h"

#include "AI/VirusAI.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetTargetNone::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);

    return Super::ExecuteTask(OwnerComp, NodeMemory);
}
