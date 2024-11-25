// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/GGFMenuWidget.h"
#include "VirusWeaponSelectMenuWidget.generated.h"

class UVirusWeaponSlotWidget;
class UButton;

/**
 *
 */
UCLASS()
class VIRUS_API UVirusWeaponSelectMenuWidget : public UGGFMenuWidget
{
    GENERATED_BODY()

protected:
    /* 컴포넌트 */

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVirusWeaponSlotWidget> WeaponSlot_0;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVirusWeaponSlotWidget> WeaponSlot_1;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVirusWeaponSlotWidget> WeaponSlot_2;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVirusWeaponSlotWidget> WeaponSlot_3;

    UPROPERTY()
    TArray<TObjectPtr<UVirusWeaponSlotWidget>> WeaponSlots;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> SelectButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> CustomButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> EscapeButton;

    /* 멤버 변수 */

    UPROPERTY()
    TMap<TObjectPtr<UButton>, int32> WeaponIDMap;

    UPROPERTY()
    TObjectPtr<UButton> SelectedWeaponButton;

protected:
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

    UFUNCTION()
    virtual void OnEscapeButtonClicked();

    UFUNCTION()
    virtual void OnSelectButtonClicked();

    UFUNCTION()
    virtual void OnCustomButtonClicked();

    UFUNCTION()
    virtual void OnWeaponSlotButtonClicked();

    virtual void SetSelected(TObjectPtr<UButton> Button);
    virtual void SetUnSelected(TObjectPtr<UButton> Button);
};
