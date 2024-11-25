// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/VirusWeaponSlotWidget.h"

#include "Components/TextBlock.h"
#include "Data/GGFEquipmentDataSubsystem.h"
#include "Data/GGFEquipmentDefinition.h"
#include "Data/GGFFireArmDataSubsystem.h"
#include "Data/GGFFireArmDefinition.h"

void UVirusWeaponSlotWidget::SetWeaponID(int32 InWeaponID)
{
    WeaponID = InWeaponID;

    if(auto EquipmentDataSubsystem = GetGameInstance()->GetSubsystem<UGGFEquipmentDataSubsystem>())
    {
        EquipmentDefinition = EquipmentDataSubsystem->GetEquipmentDefinition(WeaponID);
        if(EquipmentDefinition)
        {
            const auto& EquipmentData = EquipmentDefinition->GetData();
            WeaponNameText->SetText(FText::FromName(EquipmentData.DisplayName));
            AttackStatText->SetText(FText::FromString(AttackStatPrefixString + FString::SanitizeFloat(EquipmentData.Attack)));
        }
    }

    if(auto FireArmDataSubsystem = GetGameInstance()->GetSubsystem<UGGFFireArmDataSubsystem>())
    {
        FireArmDefinition = FireArmDataSubsystem->GetDefinition(WeaponID);
        if(FireArmDefinition)
        {
            const auto& FireArmData = FireArmDefinition->GetData();
            RPMText->SetText(FText::FromString(RPMPrefixString + FString::FromInt(FireArmData.RPM)));
            ReloadDurationText->SetText(FText::FromString(ReloadDurationPrefixString + FString::SanitizeFloat(FireArmData.ReloadDuration)));
        }
    }
}
