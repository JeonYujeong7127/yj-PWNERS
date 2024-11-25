// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StageResultWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Games/VirusGameMode.h"
#include "Games/VirusGameState.h"

class AVirusGameMode;

void UStageResultWidget::NativeConstruct()
{
    Super::NativeConstruct();

    BTClose->OnClicked.AddDynamic(this, &UStageResultWidget::OnBTCloseClicked);
}

void UStageResultWidget::OnBTCloseClicked()
{
    if(AVirusGameMode* GameMode = Cast<AVirusGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        RemoveFromParent();
        ReturnToLobby();
    }
}

void UStageResultWidget::ReturnToLobby()
{
    if(GetOwningPlayer()->GetLocalRole() == ROLE_Authority)
    {
        // Cast<AVirusGameState>(GetWorld()->GetGameState())->Loading();
        GetWorld()->ServerTravel(LevelName);
    }
}
