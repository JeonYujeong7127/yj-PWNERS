// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LoadingScreenSubsystem.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API ULoadingScreenSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    ULoadingScreenSubsystem();

    TSubclassOf<class UUserWidget> LoadingWidgetClass;

protected:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    void OnPreLoadMap(const FString& InMapName);
    void OnPostLoadMap(UWorld* LoadedWorld);
};
