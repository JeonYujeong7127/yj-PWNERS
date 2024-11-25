// Fill out your copyright notice in the Description page of Project Settings.

#include "Players/VirusStagePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Games/VirusStageGameState.h"
#include "GameFramework/GameStateBase.h"
#include "Games/VirusGameMode.h"
#include "Games/VirusStageGameMode.h"
#include "Net/UnrealNetwork.h"

void AVirusStagePlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 이벤트 바인딩
    AVirusStageGameState* GameState = CastChecked<AVirusStageGameState>(GetWorld()->GetGameState());
    GameState->OnStageResultReceived.AddDynamic(this, &ThisClass::OnStageResultReceived);
}

void AVirusStagePlayerController::ShowDieWidget()
{
    UE_LOG(LogTemp, Log, TEXT("%s: Show Die Widget Start"), *GetName());

    // UI 생성
    if(!DieWidget && DieWidgetClass)
    {
        DieWidget = CreateWidget(this, DieWidgetClass);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("%s: Create Die Widget Failed"), *GetName());
    }

    // UI 표시
    if(DieWidget)
    {
        DieWidget->AddToViewport();
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("%s: There is no DieWidget"), *GetName());
    }

    if(HasAuthority())
    {
        Cast<AVirusStageGameMode>(GetWorld()->GetAuthGameMode())->CheckEveryPlayerDie();
    }
}

void AVirusStagePlayerController::RemoveDieWidget()
{
    if(DieWidget) DieWidget->RemoveFromParent();
}

void AVirusStagePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AVirusStagePlayerController, bIsDie);
}

void AVirusStagePlayerController::OnRep_IsDie()
{
    if(bIsDie)
    {
        ShowDieWidget();
    }
    else
    {
        RemoveDieWidget();
    }
}

void AVirusStagePlayerController::OnStageResultReceived_Implementation(const FStageResult& StageResult)
{

    // 로컬 플레이어 컨트롤러가 아닌 경우 무시
    if(!IsLocalController()) return;

    // UI 생성
    if(!StageResultWidget && StageResultWidgetClass)
    {
        StageResultWidget = CreateWidget(this, StageResultWidgetClass);
    }

    // UI 표시
    if(StageResultWidget) StageResultWidget->AddToViewport();

    // UI에 결과 반영

    // TODO 폰 움직임 정지

    UE_LOG(LogTemp, Error, TEXT("StageResult: %hhd"), StageResult.bSucceed);
}
