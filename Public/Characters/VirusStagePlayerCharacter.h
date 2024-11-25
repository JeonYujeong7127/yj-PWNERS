// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusPlayerCharacter.h"
#include "VirusStagePlayerCharacter.generated.h"

/**
 * Virus 프로젝트 스테이지 전용 플레이어 캐릭터
 */
UCLASS()
class VIRUS_API AVirusStagePlayerCharacter : public AVirusPlayerCharacter
{
    GENERATED_BODY()

public:
    /* Pawn */

    virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;
    virtual void PossessedBy(AController* NewController) override;

};
