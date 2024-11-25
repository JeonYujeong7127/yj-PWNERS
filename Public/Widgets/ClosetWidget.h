// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/GGFMenuWidget.h"
#include "ClosetWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UClosetWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY()
    UUserWidget* WeaponWidget;

    UPROPERTY()
    UUserWidget* SkillWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> WeaponWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> SkillWidgetClass;

    UPROPERTY(meta = (BindWidget))
    class UButton* BT_ESC;

    UPROPERTY(meta = (BindWidget))
    class UButton* BT_Weapon;

    UPROPERTY(meta = (BindWidget))
    class UButton* BT_Skill;

    UFUNCTION()
    void OnClicked_BTESC();

    UFUNCTION()
    void OnClicked_BTWeapon();

    UFUNCTION()
    void OnClicked_BTSkill();
};
