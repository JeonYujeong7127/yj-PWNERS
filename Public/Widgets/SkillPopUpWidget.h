// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/GGFSkillDefinition.h"
#include "SkillPopUpWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API USkillPopUpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Text_SkillName;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Text_SkillDescription;

private:
    UPROPERTY()
    APlayerController* PlayerController;

    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
    virtual void SetSkillData(const FGGFSkillData& InSkillData);
};
