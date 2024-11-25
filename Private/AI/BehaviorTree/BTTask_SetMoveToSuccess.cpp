// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_SetMoveToSuccess.h"

#include "AI/VirusAI.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetMoveToSuccess::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto ExecuteResult = Super::ExecuteTask(OwnerComp, NodeMemory);

    switch(ExecuteResult)
    {
    case(EBTNodeResult::Succeeded):
        FailCount = 0;

    case(EBTNodeResult::InProgress):
        FailCount = 0;

    case(EBTNodeResult::Failed):
        FailCount++;

    case(EBTNodeResult::Aborted):
        FailCount++;
    }

    if(FailCount < 300) bIsFail = false;
    else bIsFail = true;

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISMOVETOFAIL, bIsFail);

    return ExecuteResult;
}
