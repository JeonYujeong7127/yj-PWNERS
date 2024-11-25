// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VirusWeaponSlotWidget.generated.h"

class UGGFFireArmDefinition;
class UGGFEquipmentDefinition;
class UButton;
class UTextBlock;

/**
 * VirusWeaponSelectMenuWidget에서 사용하는 서브 위젯 클래스
 */
UCLASS()
class VIRUS_API UVirusWeaponSlotWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /* 컴포넌트 */

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> SelectButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> WeaponNameText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> AttackStatText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> RPMText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ReloadDurationText;

    /* 멤버 변수 */

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    int32 WeaponID = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UGGFEquipmentDefinition> EquipmentDefinition;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UGGFFireArmDefinition> FireArmDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FString AttackStatPrefixString = "- Attack: ";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FString RPMPrefixString = "- RPM: ";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FString ReloadDurationPrefixString = "- Reload: ";

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetWeaponID(int32 InWeaponID);
};
