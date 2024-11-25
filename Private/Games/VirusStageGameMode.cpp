// Fill out your copyright notice in the Description page of Project Settings.

#include "Games/VirusStageGameMode.h"

#include "Games/TESTMultiplayerInstance.h"
#include "Games/VirusStageGameState.h"
#include "Players/VirusStagePlayerState.h"
#include "Players/VirusStagePlayerController.h"

AVirusStageGameMode::AVirusStageGameMode()
{
    GameStateClass = AVirusStageGameState::StaticClass();
    PlayerStateClass = AVirusStagePlayerState::StaticClass();
    PlayerControllerClass = AVirusStagePlayerController::StaticClass();
}

void AVirusStageGameMode::BeginPlay()
{
    Super::BeginPlay();
    Cast<UTESTMultiplayerInstance>(GetGameInstance())->bIsInGame = true;

    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

    if (FNamedOnlineSession* CurrentSession = SessionInterface->GetNamedSession(NAME_GameSession))
    {
        FName SessionName = CurrentSession->SessionName;

        FOnlineSessionSettings* SessionSettings = SessionInterface->GetSessionSettings(SessionName);
        SessionSettings->bAllowInvites = false;
        SessionSettings->bAllowJoinInProgress = false;
        SessionSettings->bAllowJoinViaPresence = false;

        SessionInterface->UpdateSession(SessionName, *SessionSettings);
    }
}

void AVirusStageGameMode::CheckEveryPlayerDie()
{
    for(FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PC = Iterator->Get();
        if(PC)
        {
            if(Cast<AVirusStagePlayerController>(PC)->bIsDie) continue;
            else return;
        }
    }

    GetWorld()->ServerTravel("Lobby_stylize");
}

void AVirusStageGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
    Super::HandleSeamlessTravelPlayer(C);

    // 팀 ID 할당
    if(IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(C->GetPlayerState<APlayerState>()))
    {
        TeamAgent->SetGenericTeamId(0);
    }
}
