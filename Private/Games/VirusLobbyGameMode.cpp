// Fill out your copyright notice in the Description page of Project Settings.

#include "Games/VirusLobbyGameMode.h"

#include "Games/VirusLobbyGameState.h"
#include "Players/VirusLobbyPlayerController.h"
#include "Players/VirusLobbyPlayerState.h"

AVirusLobbyGameMode::AVirusLobbyGameMode()
{
    GameStateClass = AVirusLobbyGameState::StaticClass();
    PlayerStateClass = AVirusLobbyPlayerState::StaticClass();
    PlayerControllerClass = AVirusLobbyPlayerController::StaticClass();
}

void AVirusLobbyGameMode::StartTimer()
{
    GetGameState<AVirusLobbyGameState>()->TimerStart();
}
