// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/GGFMenuWidget.h"
#include "SelectStageWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API USelectStageWidget : public UGGFMenuWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> BT_GameStart;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_ESC;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_Left;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_Right;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> Img_FirstStage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Img_SecondStage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Img_ThirdStage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> Img_FirstStageInGame;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Img_SecondStageInGame;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Img_ThirdStageInGame;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> Text_FirstStage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> Text_SecondStage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> Text_ThirdStage;

private:
    UFUNCTION()
    void OnClicked_BTGameStart();

    UFUNCTION()
    void Onclicked_BTESC();

    UFUNCTION()
    void Onclicked_BTLeft();

    UFUNCTION()
    void Onclicked_BTRight();

    TArray<UImage*> Images;
    TArray<UImage*> InGameImages;
    TArray<UTextBlock*> Texts;

    int32 CurrentStageNum = 1;
};
