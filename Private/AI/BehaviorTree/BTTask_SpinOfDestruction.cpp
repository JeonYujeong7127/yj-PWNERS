// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_SpinOfDestruction.h"

#include "AIController.h"
#include "AI/AICharacter/CubeBossAI.h"
#include "AI/AIController/CubeBossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Kismet/GameplayStatics.h"

UBTTask_SpinOfDestruction::UBTTask_SpinOfDestruction()
{
    NodeName = TEXT("Spin Of Destruction");

    CooldownDuration = 30.0f; // Default cooldown duration
    CooldownKey = "SpinOfDestructionCoolDown";
}

EBTNodeResult::Type UBTTask_SpinOfDestruction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    ACubeBossAI* Boss = Cast<ACubeBossAI>(AIController->GetPawn());

    Boss->SetStaticMeshToRoot();

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // 보스 체력이 75% 이하일 때만 실행
    if(BlackboardComp->GetValueAsFloat(TEXT("BossHealth")) >= Cast<ACubeBossAI>(OwnerComp.GetAIOwner()->GetPawn())->MaxHealth * 0.75)
    {
        return EBTNodeResult::Failed;
    }

    // Perform the Rain of Shutdown logic here
    if (AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn())
    {
        Cast<ACubeBossAIController>(OwnerComp.GetAIOwner())->SetIsAttacking(true);

        SetCooldown(OwnerComp);

        FTimerHandle SpinTimerHandle;
        Boss->GetWorld()->GetTimerManager().SetTimer(SpinTimerHandle, FTimerDelegate::CreateLambda([Boss, this]
        {
            StartSpinning(Boss);
            Cast<ACubeBossAI>(Boss)->SpinOfDestructionFire();
        }), 1.f, false);

        Boss->GetWorld()->GetTimerManager().SetTimer(SpinningTimerHandle, FTimerDelegate::CreateLambda([Boss, this]
        {
            if(Boss->IsValidLowLevel())
            {
                StopSpinning(Boss);
            }
        }), SpinDuration, false);

        return EBTNodeResult::Succeeded;
    }

    UE_LOG(LogTemp, Log, TEXT("Spin Of Destruction"));
    return EBTNodeResult::Succeeded;
}

void UBTTask_SpinOfDestruction::SetCooldown(UBehaviorTreeComponent& OwnerComp)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return;
    }

    float CurrentTime = OwnerComp.GetWorld()->GetTimeSeconds();
    BlackboardComp->SetValueAsFloat(CooldownKey, CurrentTime);
}

void UBTTask_SpinOfDestruction::StartSpinning(AActor* Boss)
{
    Cast<ACubeBossAI>(Boss)->bIsSpinning = true;
}

void UBTTask_SpinOfDestruction::FireProjectiles(AActor* Boss)
{
    ACubeBossAI* CubeBoss = Cast<ACubeBossAI>(Boss);

    CubeBoss->SpinOfDestructionFire();
}

void UBTTask_SpinOfDestruction::UpdateRotation(AActor* Boss)
{
    FRotator CurrentRotation = Boss->GetActorRotation();
    CurrentRotation.Yaw += 1.0f;
    Boss->SetActorRotation(CurrentRotation);
}

void UBTTask_SpinOfDestruction::StopSpinning(AActor* Boss)
{
    ACubeBossAI* CubeBoss = Cast<ACubeBossAI>(Boss);

    if (CubeBoss->IsValidLowLevel())
    {
        CubeBoss->GetWorld()->GetTimerManager().ClearTimer(FiringTimerHandle);
        Cast<ACubeBossAIController>(CubeBoss->GetController())->SetIsAttacking(false);
        CubeBoss->bIsSpinning = false;
    }
}

