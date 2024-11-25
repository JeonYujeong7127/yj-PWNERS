// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_HyperRush.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTTask_HyperRush : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_HyperRush();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    void SetCooldown(UBehaviorTreeComponent& OwnerComp);
    void RushToTarget(UBehaviorTreeComponent& OwnerComp);

    UPROPERTY(EditAnywhere, Category = "Cooldown")
    FName CooldownKey;

    UPROPERTY(EditAnywhere, Category = "Cooldown")
    float CooldownDuration;

    float RushDistance;
    int32 RushMaxCount;

    int32 RushCount;
};
