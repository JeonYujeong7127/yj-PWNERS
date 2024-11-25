// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/StartingWidget.h"

#include "Components/Button.h"
#include "GameFramework/Controller.h"
#include "Games/VirusLobbyGameState.h"
#include "Widgets/TimerWidget.h"

void UStartingWidget::NativeConstruct()
{
    Super::NativeConstruct();

    TimerWidget = Cast<UTimerWidget>(CreateWidget(this, TimerWidgetClass));

    BTStart->OnClicked.AddDynamic(this, &UStartingWidget::OnBTStartClicked);
    BTStage1->OnClicked.AddDynamic(this, &UStartingWidget::OnBTStage1Clicked);
    BTStage2->OnClicked.AddDynamic(this, &UStartingWidget::OnBTStage2Clicked);
    BTStage3->OnClicked.AddDynamic(this, &UStartingWidget::OnBTStage3Clicked);
}

void UStartingWidget::OnBTStartClicked()
{
    if(StageNum == 0)
    {
        return;
    }

    RemoveFromParent();

    Cast<AVirusLobbyGameState>(GetWorld()->GetGameState())->TimerStart();
    Cast<AVirusLobbyGameState>(GetWorld()->GetGameState())->StageNum = this->StageNum;
}
