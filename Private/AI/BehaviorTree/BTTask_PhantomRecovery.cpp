// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_PhantomRecovery.h"

#include "AIController.h"
#include "AI/AICharacter/CubeBossAI.h"
#include "AI/AIController/CubeBossAIController.h"
#include "AI/Weapon/CubeBossInstallation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

class ACubeBossAI;

UBTTask_PhantomRecovery::UBTTask_PhantomRecovery()
{
    NodeName = TEXT("Phantom Recovery");

    CooldownDuration = 30.0f; // Default cooldown duration
    CooldownKey = "PhantomRecoveryCooldown";
}

EBTNodeResult::Type UBTTask_PhantomRecovery::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Cast<ACubeBossAIController>(OwnerComp.GetAIOwner())->SetIsAttacking(true);
    Cast<ACubeBossAI>(OwnerComp.GetAIOwner()->GetPawn())->PhantomRecoveryInstall();

    return EBTNodeResult::Succeeded;
}


void UBTTask_PhantomRecovery::SetCooldown(UBehaviorTreeComponent& OwnerComp) const
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return;
    }

    float CurrentTime = OwnerComp.GetWorld()->GetTimeSeconds();
    BlackboardComp->SetValueAsFloat(CooldownKey, CurrentTime);
}
