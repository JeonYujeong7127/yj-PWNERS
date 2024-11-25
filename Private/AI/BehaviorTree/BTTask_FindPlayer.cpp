// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_FindPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPlayer::UBTTask_FindPlayer()
{
}

EBTNodeResult::Type UBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (AAIController* AIController = OwnerComp.GetAIOwner())
    {
        if (APawn* AIPawn = AIController->GetPawn())
        {
            UWorld* World = AIPawn->GetWorld();
            if (!World) return EBTNodeResult::Failed;

            float NearestDistance = FLT_MAX;
            AActor* NearestPlayer = nullptr;

            for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
            {
                if (APlayerController* PlayerController = It->Get(); PlayerController && PlayerController->GetPawn())
                {
                    float Distance = FVector::Dist(PlayerController->GetPawn()->GetActorLocation(), AIPawn->GetActorLocation());
                    if (Distance < NearestDistance)
                    {
                        NearestDistance = Distance;
                        NearestPlayer = PlayerController->GetPawn();
                    }
                }
            }

            if (NearestPlayer)
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), NearestPlayer);
                return EBTNodeResult::Succeeded;
            }
        }
    }

    return EBTNodeResult::Failed;
}
