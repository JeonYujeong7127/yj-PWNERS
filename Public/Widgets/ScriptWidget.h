// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScriptWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UScriptWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    void SetScriptStart();
    void SetScriptText(const FString Script);
    void SetSpeakerText(const FString Speaker);
    void SetSpeakerColor(const FLinearColor SpeakerColor);

    void EndScript();

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Text_Speaker;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Text_Script;
};
