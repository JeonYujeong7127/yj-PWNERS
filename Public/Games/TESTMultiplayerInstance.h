// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "TESTMultiplayerInstance.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UTESTMultiplayerInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()
public:
    void SetPlayerSkills(const FString& FirstSkillName, const FString& SecondSkillName);

    UFUNCTION(BlueprintCallable, Category = "GameInstance")
    void SetSteamRichPresence(const FString& Key, const FString& Value);

    UFUNCTION(BlueprintCallable, Category = "GameInstance")
    void ClearSteamRichPresence();

    UPROPERTY(BlueprintReadWrite)
    FString UserName = FString(TEXT("Hong gill don"));

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool bIsInGame = false;
};
