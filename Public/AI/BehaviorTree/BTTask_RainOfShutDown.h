// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RainOfShutDown.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTTask_RainOfShutDown : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_RainOfShutDown();

    UPROPERTY(EditAnywhere, Category = "Cooldown")
    FName CooldownKey;

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    void Attack(UBehaviorTreeComponent& OwnerComp);
    // void ThrowStaticMesh(UStaticMeshComponent* StaticMesh, FVector TargetLocation, class ACubeBossAI* Boss, int32 MeshIndex);
    void FallingStaticMesh(UStaticMeshComponent* StaticMesh, FVector TargetLocation, class ACubeBossAI* Boss, int32 MeshIndex);

private:
    void SetCooldown(ACubeBossAI* Boss) const;

    UPROPERTY(EditAnywhere, Category = "Cooldown")
    float CooldownDuration;

    TArray<FTransform> InitialTransforms; // To store initial positions of static meshes
};
