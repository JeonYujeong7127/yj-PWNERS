// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_FindPatrolPos.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/VirusAI.h"
#include "NavigationSystem.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "GameFramework/CharacterMovementComponent.h"

class AVirusAIBase;

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

    if (!ControllingPawn)
    {
        UE_LOG(LogTemp, Log, TEXT("ControllingPawn is null"));
        return EBTNodeResult::Failed;
    }

    AIPawn = Cast<AVirusAIBase>(ControllingPawn);

    if (nullptr == AIPawn)
    {
        UE_LOG(LogTemp, Log, TEXT("AIPawn is null"));
        return EBTNodeResult::Failed;
    }

    if(AIPawn->GetCharacterMovement()->MovementMode == MOVE_Walking)
    {
        if(FindWalkingPatrolPos(OwnerComp)) return EBTNodeResult::Succeeded;
        else return EBTNodeResult::Failed;
    }
    else if(AIPawn->GetCharacterMovement()->MovementMode == MOVE_Flying)
    {
        if(FindFlyingPatrolPos(OwnerComp)) return EBTNodeResult::Succeeded;
        else return EBTNodeResult::Failed;
    }
    else
    {
        return EBTNodeResult::Failed;
    }
}

bool UBTTask_FindPatrolPos::FindFlyingPatrolPos(UBehaviorTreeComponent& OwnerComp)
{
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerComp.GetAIOwner()->GetWorld());
    if (nullptr == NavSystem)
    {
        UE_LOG(LogTemp, Log, TEXT("NavSystem is null"));
        return false;
    }

    FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);
    float PatrolRadius = AIPawn->GetAIPatrolRadius();
    FNavLocation NextPatrolPos;

    if(NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos))
    {
        NextPatrolPos.Location.Z = FMath::RandRange(Origin.Z, Origin.Z + 100.f);
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NextPatrolPos);
        return true;
    }
    else return false;
}

bool UBTTask_FindPatrolPos::FindWalkingPatrolPos(UBehaviorTreeComponent& OwnerComp)
{
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerComp.GetAIOwner()->GetWorld());
    if (nullptr == NavSystem)
    {
        UE_LOG(LogTemp, Log, TEXT("NavSystem is null"));
        return false;
    }

    FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);
    float PatrolRadius = AIPawn->GetAIPatrolRadius();
    FNavLocation NextPatrolPos;

    if(NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NextPatrolPos);
        return true;
    }
    else return false;
}
