// Fill out your copyright notice in the Description page of Project Settings.

#include "Players/VirusPlayerState.h"

#include "Net/UnrealNetwork.h"

void AVirusPlayerState::CopyProperties(APlayerState* PlayerState)
{
    Super::CopyProperties(PlayerState);

    // SeamlessTravel로 인한 PlayerState 교체 시 유지할 데이터
    if(auto NewVirusPlayerState = Cast<AVirusPlayerState>(PlayerState))
    {
        NewVirusPlayerState->CharacterID = CharacterID;
        NewVirusPlayerState->CharacterSkinID = CharacterSkinID;
        NewVirusPlayerState->WeaponID = WeaponID;
        NewVirusPlayerState->WeaponSkinID = WeaponSkinID;
        NewVirusPlayerState->PrimarySkillID = PrimarySkillID;
        NewVirusPlayerState->SecondarySkillID = SecondarySkillID;
    }
}

void AVirusPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, CharacterID);
    DOREPLIFETIME(ThisClass, CharacterSkinID);
    DOREPLIFETIME(ThisClass, WeaponID);
    DOREPLIFETIME(ThisClass, WeaponSkinID);
    DOREPLIFETIME(ThisClass, PrimarySkillID);
    DOREPLIFETIME(ThisClass, SecondarySkillID);
}

void AVirusPlayerState::SetCharacterID(int32 NewCharacterID)
{
    ServerSetCharacterID(NewCharacterID);
}

void AVirusPlayerState::SetCharacterSkinID(int32 NewCharacterSkinID)
{
    ServerSetCharacterSkinID(NewCharacterSkinID);
}

void AVirusPlayerState::SetWeaponID(int32 NewWeaponID)
{
    ServerSetWeaponID(NewWeaponID);
}

void AVirusPlayerState::SetWeaponSkinID(int32 NewWeaponSkinID)
{
    ServerSetWeaponID(NewWeaponSkinID);
}

void AVirusPlayerState::SetPrimarySkillID(int32 NewPrimarySkillID)
{
    ServerSetPrimarySkillID(NewPrimarySkillID);
}

void AVirusPlayerState::SetSecondarySkillID(int32 NewSecondarySkillID)
{
    ServerSetSecondarySkillID(NewSecondarySkillID);
}

void AVirusPlayerState::ServerSetCharacterID_Implementation(int32 NewCharacterID)
{
    CharacterID = NewCharacterID;
}

void AVirusPlayerState::ServerSetCharacterSkinID_Implementation(int32 NewCharacterSkinID)
{
    CharacterSkinID = NewCharacterSkinID;
}

void AVirusPlayerState::ServerSetWeaponID_Implementation(int32 NewWeaponID)
{
    WeaponID = NewWeaponID;
}

void AVirusPlayerState::ServerSetWeaponSkinID_Implementation(int32 NewWeaponSkinID)
{
    WeaponSkinID = NewWeaponSkinID;
}

void AVirusPlayerState::ServerSetPrimarySkillID_Implementation(int32 NewPrimarySkillID)
{
    PrimarySkillID = NewPrimarySkillID;
}

void AVirusPlayerState::ServerSetSecondarySkillID_Implementation(int32 NewSecondarySkillID)
{
    SecondarySkillID = NewSecondarySkillID;
}

void AVirusPlayerState::OnRep_CharacterID(int32 OldCharacterID)
{
}

void AVirusPlayerState::OnRep_CharacterSkinID(int32 OldCharacterSkinID)
{
}

void AVirusPlayerState::OnRep_WeaponID(int32 OldWeaponID)
{
}

void AVirusPlayerState::OnRep_WeaponSkinID(int32 OldWeaponSkinID)
{
}

void AVirusPlayerState::OnRep_PrimarySkillID(int32 OldPrimarySkillID)
{
}

void AVirusPlayerState::OnRep_SecondarySkillID(int32 OldSecondarySkillID)
{
}
