// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/PlayerNameWidget.h"

#include "Components/TextBlock.h"

void UPlayerNameWidget::SetPlayerName(FString NewPlayerName)
{
    PlayerNameText->SetText(FText::FromString(NewPlayerName));
}
