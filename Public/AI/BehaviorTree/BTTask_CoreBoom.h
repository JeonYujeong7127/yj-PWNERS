// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CoreBoom.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTTask_CoreBoom : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_CoreBoom();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    UPROPERTY(EditAnywhere, Category = "Cooldown")
    FName CooldownKey;

    UPROPERTY(EditAnywhere, Category = "Cooldown")
    float CooldownDuration;

    void SetCooldown(UBehaviorTreeComponent& OwnerComp);
};
