// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AnyoneInAttackRange.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTService_AnyoneInAttackRange : public UBTService
{
	GENERATED_BODY()

    UBTService_AnyoneInAttackRange();
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
