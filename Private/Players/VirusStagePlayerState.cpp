// Fill out your copyright notice in the Description page of Project Settings.

#include "Players/VirusStagePlayerState.h"

#include "Engine/Texture2D.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Steam/steam_api.h"

AVirusStagePlayerState::AVirusStagePlayerState()
{
    SteamAvatar = nullptr;
}

void AVirusStagePlayerState::BeginPlay()
{
    Super::BeginPlay();

    GetSteamAvatar();
}

void AVirusStagePlayerState::GetSteamAvatar()
{
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
        if (Identity.IsValid() && SteamAPI_Init())
        {
            FUniqueNetIdPtr UserId = Identity->GetUniquePlayerId(0);
            if (UserId.IsValid())
            {
                CSteamID SteamUserID = SteamUser()->GetSteamID();

                // Get the small avatar (32x32)
                int Image = SteamFriends()->GetSmallFriendAvatar(SteamUserID);

                if (Image == -1)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to get avatar."));
                    return;
                }

                // Get the image size
                uint32 Width, Height;
                bool bIsValid = SteamUtils()->GetImageSize(Image, &Width, &Height);

                if (!bIsValid)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to get avatar size."));
                    return;
                }

                // Get the image data
                TArray<uint8> ImageRGBA;
                ImageRGBA.SetNumUninitialized(Width * Height * 4);

                bIsValid = SteamUtils()->GetImageRGBA(Image, ImageRGBA.GetData(), ImageRGBA.Num());

                if (!bIsValid)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to get avatar RGBA data."));
                    return;
                }

                // Create the texture
                UTexture2D* AvatarTexture = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);

                if (!AvatarTexture)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to create texture."));
                    return;
                }

                // Update the texture with the avatar data
                void* TextureData = AvatarTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
                FMemory::Memcpy(TextureData, ImageRGBA.GetData(), ImageRGBA.Num());
                AvatarTexture->PlatformData->Mips[0].BulkData.Unlock();

                // Update the texture resource
                AvatarTexture->UpdateResource();

                // Assign the avatar texture to the PlayerState
                SteamAvatar = AvatarTexture;
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem not found."));
    }
}
