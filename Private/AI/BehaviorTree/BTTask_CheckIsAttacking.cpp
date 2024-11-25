// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_CheckIsAttacking.h"

#include "AIController.h"
#include "AI/AICharacter/CubeBossAI.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_CheckIsAttacking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    BlackboardComp->SetValueAsBool(TEXT("IsAttacking"), Cast<ACubeBossAI>(OwnerComp.GetAIOwner()->GetPawn())->bIsAttacking);

    return Super::ExecuteTask(OwnerComp, NodeMemory);
}
