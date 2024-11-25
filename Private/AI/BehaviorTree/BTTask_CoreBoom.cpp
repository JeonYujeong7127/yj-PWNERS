// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_CoreBoom.h"

#include "AIController.h"
#include "AI/AICharacter/CubeBossAI.h"
#include "AI/AIController/CubeBossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_CoreBoom::UBTTask_CoreBoom()
{
    NodeName = TEXT("Core Boom");

    CooldownDuration = 150.0f; // Default cooldown duration
    CooldownKey = "CoreBoomCoolDown";
}

EBTNodeResult::Type UBTTask_CoreBoom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Cast<ACubeBossAIController>(OwnerComp.GetAIOwner())->SetIsAttacking(true);

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    if (OwnerComp.GetAIOwner()->HasAuthority())
    {
        Cast<ACubeBossAI>(OwnerComp.GetAIOwner()->GetPawn())->CoreBoom();
    }

    // Set the cooldown
    SetCooldown(OwnerComp);

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
    {
        if(OwnerComp.IsValidLowLevel())
        {
            Cast<ACubeBossAIController>(OwnerComp.GetAIOwner())->SetIsAttacking(false);
        }
    }), 5.0f, false);

    UE_LOG(LogTemp, Log, TEXT("Core Boom"));

    return EBTNodeResult::Succeeded;
}

void UBTTask_CoreBoom::SetCooldown(UBehaviorTreeComponent& OwnerComp)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return;
    }

    // Store the current time in the blackboard
    float CurrentTime = OwnerComp.GetWorld()->GetTimeSeconds();
    BlackboardComp->SetValueAsFloat(CooldownKey, CurrentTime);

    // Set a timer to reset the cooldown after the duration
    FTimerHandle TimerHandle;
    OwnerComp.GetWorld()->GetTimerManager().SetTimer(TimerHandle, [BlackboardComp, this]()
    {
        if(BlackboardComp->IsValidLowLevel())
        {
            BlackboardComp->SetValueAsFloat(CooldownKey, 0.0f);
        }
    }, CooldownDuration, false);
}
