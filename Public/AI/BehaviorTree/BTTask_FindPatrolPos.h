// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolPos.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    bool FindFlyingPatrolPos(UBehaviorTreeComponent& OwnerComp);
    bool FindWalkingPatrolPos(UBehaviorTreeComponent& OwnerComp);

    UPROPERTY()
    class APawn* ControllingPawn;

    UPROPERTY()
    class AVirusAIBase* AIPawn;
};
