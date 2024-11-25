// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CheckCooldown.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTTask_CheckCooldown : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_CheckCooldown();

    /** Cooldown key to check */
    UPROPERTY(EditAnywhere, Category = "AI")
    FName CooldownKey;

    /** Cooldown duration in seconds */
    UPROPERTY(EditAnywhere, Category = "AI")
    float CooldownDuration;

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
