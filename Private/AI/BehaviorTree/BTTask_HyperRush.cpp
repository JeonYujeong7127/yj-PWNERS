// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_HyperRush.h"

#include "AIController.h"
#include "AI/AICharacter/CubeBossAI.h"
#include "AI/AIController/CubeBossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

UBTTask_HyperRush::UBTTask_HyperRush()
{
    NodeName = TEXT("Hyper Rush");

    CooldownDuration = 10.0f; // Default cooldown duration
    CooldownKey = "HyperRushCoolDown";

    RushDistance = 3000.0f; // Set the desired rush distance (map end distance)
    RushMaxCount = 3;
    RushCount = 0;
}

EBTNodeResult::Type UBTTask_HyperRush::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // 20미터 이상 멀어졌을 경우에만 HyperRush 실행
    if(BlackboardComp->GetValueAsFloat(TEXT("DistanceToPlayer")) < 2000.f)
    {
        UE_LOG(LogTemp, Log, TEXT("player is too close: %f"), BlackboardComp->GetValueAsFloat(TEXT("DistanceToPlayer")));
        return EBTNodeResult::Failed;
    }

    if (AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn())
    {
        Cast<ACubeBossAIController>(OwnerComp.GetAIOwner())->SetIsAttacking(true);
        Cast<ACubeBossAI>(OwnerActor)->GetCapsuleComponent()->SetCapsuleHalfHeight(100.f);

        RushToTarget(OwnerComp);
    }
    return EBTNodeResult::Succeeded;
}

void UBTTask_HyperRush::SetCooldown(UBehaviorTreeComponent& OwnerComp)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return;
    }

    float CurrentTime = OwnerComp.GetWorld()->GetTimeSeconds();
    BlackboardComp->SetValueAsFloat(CooldownKey, CurrentTime);
}

void UBTTask_HyperRush::RushToTarget(UBehaviorTreeComponent& OwnerComp)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* AIPawn = AIController ? AIController->GetPawn() : nullptr;

    if (!AIPawn)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor"))))
    {
        Cast<ACubeBossAI>(AIPawn)->bIsDamageable = true;

        UE_LOG(LogTemp, Log, TEXT("Rush To Target: %s"), *TargetActor->GetName());

        // TargetActor와의 거리 계산
        FVector Direction = (TargetActor->GetActorLocation() - AIPawn->GetActorLocation()).GetSafeNormal();
        float DistanceToTarget = FVector::Dist(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

        // 원하는 이동 거리 설정 (20m)
        float DesiredDistance = 2000.f;

        // 실제 이동 거리를 계산
        float MoveDistance = FMath::Max(DesiredDistance, DistanceToTarget);

        // 이동할 벡터 계산
        FVector LaunchVelocity = Direction * MoveDistance * 10.f;

        // AI 캐릭터를 타겟 위치로 이동
        Cast<ACharacter>(AIPawn)->LaunchCharacter(LaunchVelocity, true, false);

        AIController->MoveToLocation(LaunchVelocity, -1.0f, true, true, false, true, 0, true);

        FTimerHandle TimerHandle;
        AIPawn->GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, &OwnerComp]()
        {
            RushCount++;

            UE_LOG(LogTemp, Log, TEXT("RushCount: %d"), RushCount)

            if (RushCount < RushMaxCount)
            {
                RushToTarget(OwnerComp);
            }
            else
            {
                Cast<ACubeBossAIController>(OwnerComp.GetAIOwner())->SetIsAttacking(false);
                SetCooldown(OwnerComp);
                RushCount = 0;

                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            }
        }), 1.f, false);
    }
    else
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }
}
