// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageClearWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UStageClearWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(EditAnywhere, Category = "Media")
    class UMediaPlayer* MediaPlayer;

    UPROPERTY(EditAnywhere, Category = "Media")
    class UMediaSource* MediaSource;

    UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* WidgetSwitcher;
};
