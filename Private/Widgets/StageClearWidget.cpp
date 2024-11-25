// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StageClearWidget.h"

#include "MediaPlayer.h"
#include "Components/WidgetSwitcher.h"

void UStageClearWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // MediaPlayer와 MediaSource를 설정합니다.
    if (MediaPlayer && MediaSource)
    {
        MediaPlayer->OpenSource(MediaSource);
        MediaPlayer->Play();
    }
}
