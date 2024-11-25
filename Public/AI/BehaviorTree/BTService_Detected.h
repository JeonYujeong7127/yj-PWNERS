// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detected.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTService_Detected : public UBTService
{
	GENERATED_BODY()

public:
    UBTService_Detected();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
