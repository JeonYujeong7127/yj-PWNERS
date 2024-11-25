// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusPlayerState.h"
#include "VirusStagePlayerState.generated.h"

/**
 * Virus 프로젝트 스테이지 전용 플레이어 스테이트 클래스
 */
UCLASS()
class VIRUS_API AVirusStagePlayerState : public AVirusPlayerState
{
    GENERATED_BODY()

public:
    AVirusStagePlayerState();
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Steam")
    class UTexture2D* SteamAvatar;

private:
    UFUNCTION(BlueprintCallable, Category = "Steam")
    void GetSteamAvatar();
};
