// Fill out your copyright notice in the Description page of Project Settings.

#include "Players/VirusLobbyPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/TimerWidget.h"
#include "GameFramework/GameStateBase.h"
#include "Widgets/StageTimerWidget.h"
#include "Virus.h"
#include "Widgets/ScriptWidget.h"

void AVirusLobbyPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AVirusLobbyPlayerController::TimerStart()
{
    TimerWidget = Cast<UTimerWidget>(ShowWidget(LobbyTimerWidgetClass));
}

void AVirusLobbyPlayerController::GameStart()
{
    StageTimerStart();
    ShowMainPlayWidget();
    // ServerTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
}

void AVirusLobbyPlayerController::GameEnd()
{
    GetWorld()->GetTimerManager().ClearTimer(StageTimerHandle);
}

void AVirusLobbyPlayerController::FloatLoadingScreen()
{
    NET_LOG(LogTemp, Log, TEXT("%s"), TEXT("Floating"));
    ShowWidget(LoadingWidgetClass);
    bIsLoading = false;
}

void AVirusLobbyPlayerController::TimerAllReady()
{
    TimerWidget->StartReadyCountdownTimer();
}

void AVirusLobbyPlayerController::TimerNotReady()
{
    TimerWidget->StopReadyCountdownTimer();
}

void AVirusLobbyPlayerController::StageTimerStart()
{
    if(UUserWidget* UserWidget = CreateWidget(GetWorld(), StageTimerWidgetClass))
    {
        UserWidget->AddToViewport();
        StageTimerWidget = Cast<UStageTimerWidget>(UserWidget);

        GetWorld()->GetTimerManager().SetTimer(StageTimerHandle, FTimerDelegate::CreateLambda([&]
        {
            StageTimerWidget->SetTextTimeBlock(ClientTime);
            ClientTime += 0.001;
        }), 0.001f, true, 0);


        UE_LOG(LogTemp, Log, TEXT("StageTimerStart"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("There is no StageTimer"));
    }
}

void AVirusLobbyPlayerController::ShowMainPlayWidget()
{
    if(UUserWidget* MainPlayWidget = CreateWidget(GetWorld(), MainPlayerWidgetClass))
    {
        MainPlayWidget->AddToViewport();
    }
}

void AVirusLobbyPlayerController::OnRep_bIsLoading()
{
    NET_LOG(LogTemp, Log, TEXT("%s"), TEXT("Floating"));

    if(bIsLoading)
    {
        FloatLoadingScreen();
    }
}

void AVirusLobbyPlayerController::OnRep_bIsGameEnd()
{
    if(bIsGameEnd)
    {
        GameEnd();
    }
}

void AVirusLobbyPlayerController::OnRep_UserWidgetClass()
{
    ShowWidget(UserWidgetClass);
}

void AVirusLobbyPlayerController::OnRep_bIsTimerStart()
{
    if(bIsTimerStart)
    {
        TimerStart();
        bIsTimerStart = false;
    }
}

void AVirusLobbyPlayerController::OnRep_bIsAllReady()
{
    if(bIsAllReady) TimerAllReady();
    else TimerNotReady();
}

void AVirusLobbyPlayerController::OnRep_bIsGameStart()
{
    GameStart();
}

void AVirusLobbyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AVirusLobbyPlayerController, bIsLoading);
    DOREPLIFETIME(AVirusLobbyPlayerController, bIsGameStart);
    DOREPLIFETIME(AVirusLobbyPlayerController, bIsGameEnd);
    DOREPLIFETIME(AVirusLobbyPlayerController, bIsTimerStart);
    DOREPLIFETIME(AVirusLobbyPlayerController, bIsAllReady);
    DOREPLIFETIME(AVirusLobbyPlayerController, UserWidgetClass);
    DOREPLIFETIME(AVirusLobbyPlayerController, TimerWidget);
}

