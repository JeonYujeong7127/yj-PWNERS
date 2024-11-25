// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SpinOfDestruction.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTTask_SpinOfDestruction : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_SpinOfDestruction();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    UPROPERTY(EditAnywhere, Category = "Cooldown")
    FName CooldownKey;

    UPROPERTY(EditAnywhere, Category = "Cooldown")
    float CooldownDuration;

    void SetCooldown(UBehaviorTreeComponent& OwnerComp);

    void StartSpinning(AActor* Boss);
    void FireProjectiles(AActor* Boss);
    void UpdateRotation(AActor* Boss);
    void StopSpinning(AActor* Boss);

    FTimerHandle SpinningTimerHandle;
    FTimerHandle FiringTimerHandle;
    float SpinDuration = 10.0f;
};
