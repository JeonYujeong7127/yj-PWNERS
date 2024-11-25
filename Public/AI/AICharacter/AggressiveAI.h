// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusAIBase.h"
#include "AggressiveAI.generated.h"

UCLASS()
class VIRUS_API AAggressiveAI : public AVirusAIBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAggressiveAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
    UAnimSequence* AnimAttack;
};
