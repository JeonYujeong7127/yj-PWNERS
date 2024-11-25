// Copyright Epic Games, Inc. All Rights Reserved.

#include "Games/VirusGameMode.h"

#include "Games/VirusGameState.h"
#include "Players/VirusPlayerController.h"
#include "Players/VirusPlayerState.h"

AVirusGameMode::AVirusGameMode()
{
    // SeamlessTravel 사용 설정
    bUseSeamlessTravel = true;

    // 기본 설정
	GameStateClass = AVirusGameState::StaticClass();
    PlayerStateClass = AVirusPlayerState::StaticClass();
    PlayerControllerClass = AVirusPlayerController::StaticClass();

    /* GGFGameMode */
    bAllPlayerSameTeam = true;
}
