// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusGameMode.h"
#include "VirusStageGameMode.generated.h"

class AGGFEquipment;

// TODO 2차 빌드용 임시 코드입니다.
/**
 * Virus 프로젝트 스테이지 전용 게임 모드 클래스
 */
UCLASS()
class VIRUS_API AVirusStageGameMode : public AVirusGameMode
{
	GENERATED_BODY()

public:
    AVirusStageGameMode();
    virtual void BeginPlay() override;
    void CheckEveryPlayerDie();

    virtual void HandleSeamlessTravelPlayer(AController*& C) override;
};
