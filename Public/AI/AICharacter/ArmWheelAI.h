// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "ArmWheelAI.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API AArmWheelAI : public AVirusAIBase
{
	GENERATED_BODY()

public:
    AArmWheelAI();
    virtual void BeginPlay() override;
};
