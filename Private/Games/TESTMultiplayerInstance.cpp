// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/TESTMultiplayerInstance.h"
#include "ThirdParty/Steamworks/Steamv153/sdk/public/steam/steam_api.h"

void UTESTMultiplayerInstance::SetPlayerSkills(const FString& FirstSkillName, const FString& SecondSkillName)
{
    UE_LOG(LogTemp, Log, TEXT("Fisrt: %s, Second: %s"), *FirstSkillName, *SecondSkillName);
}

void UTESTMultiplayerInstance::SetSteamRichPresence(const FString& Key, const FString& Value)
{
    SteamFriends()->SetRichPresence("status", "In Game");

}

void UTESTMultiplayerInstance::ClearSteamRichPresence()
{
    SteamFriends()->ClearRichPresence();
}
