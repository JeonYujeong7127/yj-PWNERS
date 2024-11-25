// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/VirusLobbyPlayerCharacter.h"

#include "Components/GGFCharacterManager.h"
#include "Components/GGFCharacterSkinManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Players/VirusPlayerState.h"

AVirusLobbyPlayerCharacter::AVirusLobbyPlayerCharacter()
{
    // TODO 임시 코드
    // Unarmed Crouch 애니메이션이 없는 관계로 로비에서는 앉기 기능 비활성화
    GetCharacterMovement()->NavAgentProps.bCanCrouch = false;
}

void AVirusLobbyPlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if(auto NewVirusPlayerState = Cast<AVirusPlayerState>(GetPlayerState()))
    {
        if(NewVirusPlayerState->GetCharacterID() >= 0) GetCharacterManager()->SetCharacterByID(NewVirusPlayerState->GetCharacterID());
        if(NewVirusPlayerState->GetCharacterSkinID() >= 0) GetSkinManager()->SetSkinByID(NewVirusPlayerState->GetCharacterSkinID());
    }
}
