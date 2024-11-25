// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StageTimerWidget.h"

#include "Virus.h"
#include "Components/TextBlock.h"
#include "Games/VirusStageGameState.h"

void UStageTimerWidget::NativeConstruct()
{
    Super::NativeConstruct();
    VirusStageGameState = Cast<AVirusStageGameState>(GetWorld()->GetGameState());
    // ServerTime = VirusStageGameState->ServerTime;
}

void UStageTimerWidget::SetTextTimeBlock(const double Time)
{
    // 시간 변환: Time은 밀리초 단위입니다.

    int32 TruncatedMilliseconds = static_cast<int32>(Time * 1000.0); // 소수점 아래를 버림

    int32 TotalSeconds = (TruncatedMilliseconds / 1000);
    int32 TotalMinutes = TotalSeconds / 60;
    int32 TotalMilliseconds = (Time - TotalSeconds) * 100;

    // 포맷팅된 시간 문자열 (분:초 :밀리초)
    FString Text = FString::Printf(TEXT("%02d  %02d  %02d"), TotalMinutes, TotalSeconds % 60, TotalMilliseconds);

    // 텍스트 블록에 포맷팅된 시간 문자열 설정
    TextTimeBlock->SetText(FText::FromString(Text));

}
