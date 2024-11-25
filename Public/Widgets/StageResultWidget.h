// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/GGFInteractionMenuWidget.h"
#include "StageResultWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UStageResultWidget : public UGGFInteractionMenuWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton* BTClose;

    UFUNCTION()
    void OnBTCloseClicked();

    void ReturnToLobby();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
    FString LevelName;
};
