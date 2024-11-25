// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_CheckCooldown.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckCooldown::UBTTask_CheckCooldown()
{
    NodeName = TEXT("Check Cooldown");
}

EBTNodeResult::Type UBTTask_CheckCooldown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (AAIController* AIController = OwnerComp.GetAIOwner())
    {
        if (APawn* AIPawn = AIController->GetPawn())
        {
            float LastUsedTime = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(CooldownKey);
            float CurrentTime = GetWorld()->GetTimeSeconds();

            if (CurrentTime - LastUsedTime >= CooldownDuration)
            {
                UE_LOG(LogTemp, Log, TEXT("CurrentTime: %f CooldownKey: %s"), CurrentTime, *CooldownKey.ToString());

                // Cooldown has expired
                OwnerComp.GetBlackboardComponent()->SetValueAsFloat(CooldownKey, CurrentTime);
                return EBTNodeResult::Succeeded;
            }
        }
    }
    return EBTNodeResult::Failed;
}
