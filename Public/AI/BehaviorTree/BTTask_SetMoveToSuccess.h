// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_SetMoveToSuccess.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UBTTask_SetMoveToSuccess : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
    bool bIsFail = false;
    int32 FailCount = 0;
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
