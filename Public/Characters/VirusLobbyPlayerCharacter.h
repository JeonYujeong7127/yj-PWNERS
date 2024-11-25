// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusPlayerCharacter.h"
#include "VirusLobbyPlayerCharacter.generated.h"

/**
 * Virus 프로젝트 로비 전용 플레이어 캐릭터
 */
UCLASS()
class VIRUS_API AVirusLobbyPlayerCharacter : public AVirusPlayerCharacter
{
    GENERATED_BODY()

public:
    AVirusLobbyPlayerCharacter();

    /* Pawn */

    virtual void PossessedBy(AController* NewController) override;
};
