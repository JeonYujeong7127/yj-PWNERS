// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFPlayerController.h"
#include "VirusPlayerController.generated.h"

/**
 * Virus 프로젝트 전용 플레이어 컨트롤러
 */
UCLASS()
class VIRUS_API AVirusPlayerController : public AGGFPlayerController
{
    GENERATED_BODY()

public:
    UUserWidget* ShowWidget(TSubclassOf<UUserWidget> VUserWidgetClass) const;
    void FloatScript();

    UPROPERTY()
    class UScriptWidget* ScriptWidget;

protected:
    virtual void OnSpectateNextActionTriggered_Implementation() override;
    virtual void OnSpectatePreviousActionTriggered_Implementation() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> ScriptWidgetClass;
};
