// Fill out your copyright notice in the Description page of Project Settings.

#include "Players/VirusPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/ScriptWidget.h"

void AVirusPlayerController::FloatScript()
{
    ScriptWidget = Cast<UScriptWidget>(ShowWidget(ScriptWidgetClass));
}

UUserWidget* AVirusPlayerController::ShowWidget(TSubclassOf<UUserWidget> VUserWidgetClass) const
{
    if(UUserWidget* UserWidget = CreateWidget(GetWorld(), VUserWidgetClass))
    {
        UserWidget->AddToViewport();
        return UserWidget;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("There is no UserWidget"));
        return nullptr;
    }
}

void AVirusPlayerController::OnSpectateNextActionTriggered_Implementation()
{
    ServerViewNextPlayer();
}

void AVirusPlayerController::OnSpectatePreviousActionTriggered_Implementation()
{
    ServerViewPrevPlayer();
}
