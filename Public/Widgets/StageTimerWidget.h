// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageTimerWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UStageTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    void SetTextTimeBlock(double Time);

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextTimeBlock;

    UPROPERTY()
    class AVirusStageGameState* VirusStageGameState;

    double ServerTime;


    FTimerHandle TimerHandle;
};
