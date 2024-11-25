// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ScriptWidget.h"

#include "Components/TextBlock.h"

void UScriptWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UScriptWidget::SetScriptStart()
{
    Text_Script->SetVisibility(ESlateVisibility::Visible);
    Text_Speaker->SetVisibility(ESlateVisibility::Visible);
}

void UScriptWidget::SetScriptText(const FString Script)
{
    Text_Script->SetText(FText::FromString(Script));
}

void UScriptWidget::SetSpeakerText(const FString Speaker)
{
    Text_Speaker->SetText(FText::FromString(Speaker));
}

void UScriptWidget::SetSpeakerColor(const FLinearColor SpeakerColor)
{
    Text_Speaker->SetColorAndOpacity(SpeakerColor);
}

void UScriptWidget::EndScript()
{
    RemoveFromParent();
}
