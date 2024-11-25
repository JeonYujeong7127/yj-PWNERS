// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TimerWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UTimerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    Img_Ready->SetOpacity(0);
    TextReadyCountNum->SetOpacity(0);

    GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, FTimerDelegate::CreateLambda([this]
    {
        RemainingTime -= 0.01;

        UpdateCountdownTimer();

        if (RemainingTime <= 0.0f)
        {
            GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
        }
    }), 0.01f, true);
}

void UTimerWidget::NativeDestruct()
{
    Super::NativeDestruct();
    GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(ReadyCountdownTimerHandle);
}

void UTimerWidget::UpdateCountdownTimer()
{
    // 시간 형식화
    FString FormattedTime = FormatTime(RemainingTime);

    // 텍스트 블록 업데이트
    if (TextTimeoutNum)
    {
        TextTimeoutNum->SetText(FText::FromString(FormattedTime));
    }
}

void UTimerWidget::StartReadyCountdownTimer()
{
    if(!bIsReadyTimerStart)
    {
        bIsReadyTimerStart = true;
        ReadyRemainingTime = 5.f;
        Img_Ready->SetOpacity(1);
        TextReadyCountNum->SetOpacity(1);

        GetWorld()->GetTimerManager().SetTimer(ReadyCountdownTimerHandle, FTimerDelegate::CreateLambda([this]
            {
                UpdateReadyCountdownTimer();

                if(ReadyRemainingTime <= 0)
                {
                    GetWorld()->GetTimerManager().ClearTimer(ReadyCountdownTimerHandle);
                }
            }), 0.01f, true);
    }
}

void UTimerWidget::StopReadyCountdownTimer()
{
    bIsReadyTimerStart = false;

    GetWorld()->GetTimerManager().ClearTimer(ReadyCountdownTimerHandle);
    Img_Ready->SetOpacity(0);
    TextReadyCountNum->SetOpacity(0);
}

void UTimerWidget::UpdateReadyCountdownTimer()
{
    // 남은 시간 감소
    ReadyRemainingTime -= 0.01f;

    // 시간 형식화
    FString FormattedTime = FormatTime(ReadyRemainingTime);

    // 텍스트 블록 업데이트
    if (TextTimeoutNum)
    {
        TextReadyCountNum->SetText(FText::FromString(FormattedTime));
    }
}

FString UTimerWidget::FormatTime(float TimeInSeconds) const
{
    int8 Minutes = FMath::FloorToInt(TimeInSeconds / 60.0f);
    int8 Seconds = FMath::FloorToInt(TimeInSeconds) % 60;
    int8 Milliseconds = FMath::RoundToInt((TimeInSeconds - FMath::FloorToInt(TimeInSeconds)) * 100);

    // "2  10  23" 형식의 문자열 생성
    return FString::Printf(TEXT("%d:%02d:%02d"), Minutes, Seconds, Milliseconds);
}
