// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/VirusStagePlayerCharacter.h"

#include "Components/GGFCharacterManager.h"
#include "Components/GGFCharacterSkinManager.h"
#include "Components/GGFEquipmentManager.h"
#include "Components/GGFSkillManager.h"
#include "Players/VirusPlayerState.h"
#include "GGFSkillGameplayTags.h"
#include "Interfaces/GGFEquipmentInterface.h"

void AVirusStagePlayerCharacter::OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
    Super::OnPlayerStateChanged(NewPlayerState, OldPlayerState);

    // TODO 임시코드
    if(auto SelectedEquipment = GetEquipmentManager()->GetSelectedEquipment())
    {
        if(SelectedEquipment->Implements<UGGFEquipmentInterface>())
        {
            IGGFEquipmentInterface::Execute_Deactivate(SelectedEquipment);
            IGGFEquipmentInterface::Execute_Activate(SelectedEquipment);
        }
    }
}

void AVirusStagePlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if(auto NewVirusPlayerState = Cast<AVirusPlayerState>(GetPlayerState()))
    {
        if(NewVirusPlayerState->GetCharacterID() >= 0) GetCharacterManager()->SetCharacterByID(NewVirusPlayerState->GetCharacterID());
        if(NewVirusPlayerState->GetCharacterSkinID() >= 0) GetSkinManager()->SetSkinByID(NewVirusPlayerState->GetCharacterSkinID());
        if(NewVirusPlayerState->GetWeaponID() >= 0) GetEquipmentManager()->AddEquipmentByID(NewVirusPlayerState->GetWeaponID());
        // if(NewVirusPlayerState->WeaponSkinID >= 0) 무기 스킨 설정
        if(NewVirusPlayerState->GetPrimarySkillID() >= 0) GetSkillManager()->SetSkillSlotByID(Input::Skill::Q, NewVirusPlayerState->GetPrimarySkillID());
        if(NewVirusPlayerState->GetSecondarySkillID() >= 0) GetSkillManager()->SetSkillSlotByID(Input::Skill::E, NewVirusPlayerState->GetSecondarySkillID());
    }
}
