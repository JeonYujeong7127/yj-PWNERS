// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CheckDistanceAndHealth.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTTask_CheckDistanceAndHealth : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_CheckDistanceAndHealth();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    void UpdateBlackboard(UBehaviorTreeComponent& OwnerComp, APawn* AIPawn, APawn* TargetPawn);
};
