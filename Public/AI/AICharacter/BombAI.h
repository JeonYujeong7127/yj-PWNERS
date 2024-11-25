// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "BombAI.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API ABombAI : public AVirusAIBase
{
	GENERATED_BODY()

public:
    ABombAI();
    virtual void BeginPlay() override;

};
