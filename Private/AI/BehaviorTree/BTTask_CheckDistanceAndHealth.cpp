// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_CheckDistanceAndHealth.h"

#include "AIController.h"
#include "AI/AICharacter/CubeBossAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckDistanceAndHealth::UBTTask_CheckDistanceAndHealth()
{
    NodeName = TEXT("Check Distance and Health");
}

EBTNodeResult::Type UBTTask_CheckDistanceAndHealth::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
    if (!TargetPawn)
    {
        return EBTNodeResult::Failed;
    }

    UpdateBlackboard(OwnerComp, AIPawn, TargetPawn);

    return EBTNodeResult::Succeeded;
}

void UBTTask_CheckDistanceAndHealth::UpdateBlackboard(UBehaviorTreeComponent& OwnerComp, APawn* AIPawn, APawn* TargetPawn)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return;
    }

    float Distance = FVector::Dist(AIPawn->GetActorLocation(), TargetPawn->GetActorLocation());
    float BossHealth = Cast<ACubeBossAI>(AIPawn)->Health; // Assuming GetHealth() is a method of your AI character

    BlackboardComp->SetValueAsFloat(TEXT("DistanceToPlayer"), Distance);
    BlackboardComp->SetValueAsFloat(TEXT("BossHealth"), BossHealth);

    // 보스 체력 50% 이하일 때 2페이즈 진입
    if(BossHealth <= Cast<ACubeBossAI>(AIPawn)->MaxHealth * 0.5)
    {
        BlackboardComp->SetValueAsBool(TEXT("IsInSecondPhase"), true);
    }
}
