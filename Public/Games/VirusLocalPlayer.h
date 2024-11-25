// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"
#include "VirusLocalPlayer.generated.h"

/**
 * Virus 프로젝트 전용 로컬 플레이어
 */
UCLASS()
class VIRUS_API UVirusLocalPlayer : public ULocalPlayer
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float InputYawScale = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float InputPitchScale = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float InputRollScale = 1;

    UFUNCTION(BlueprintCallable)
    void SetInputScale(float Value);

    UFUNCTION(BlueprintCallable)
    float GetInputScale() { return InputYawScale; };
};
