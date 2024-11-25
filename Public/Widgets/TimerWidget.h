// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    FTimerHandle CountdownTimerHandle;
    FTimerHandle ReadyCountdownTimerHandle;

    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    void UpdateCountdownTimer();
    void StartReadyCountdownTimer();
    void StopReadyCountdownTimer();
    void UpdateReadyCountdownTimer();

    float RemainingTime = 180.0f;
    float ReadyRemainingTime = 5.0f;
    bool bIsReadyTimerStart = false;

    FString FormatTime(float TimeInSeconds) const;

    // Timeout(강제 시작)까지 몇 초 남았는지 보여주는 텍스트 블록
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextTimeoutNum;

    // 모두 준비된 후 5초 카운트하는 텍스트 블록
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextReadyCountNum;

    UPROPERTY(meta = (BindWidget))
    class UImage* Img_Ready;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> LoadingWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Level)
    FString LevelName;

    UPROPERTY(BlueprintReadWrite, Category = Timer)
    float TimeOutSecond = 180.0f;

    int32 PassedTime = 0;

private:
    FTimerHandle GlobalHandle;
};
