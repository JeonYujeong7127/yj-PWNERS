// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusGameMode.h"
#include "VirusLobbyGameMode.generated.h"

/**
 * Virus 프로젝트 로비 전용 게임 모드 클래스
 */
UCLASS()
class VIRUS_API AVirusLobbyGameMode : public AVirusGameMode
{
    GENERATED_BODY()

public:
    AVirusLobbyGameMode();

    // 스타트 타이머 관련 함수
    void StartTimer();
};
