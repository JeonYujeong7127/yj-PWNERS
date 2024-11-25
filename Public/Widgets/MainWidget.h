// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/GGFMenuWidget.h"
#include "MainWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UMainWidget : public UGGFMenuWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton* BTStart;

    UPROPERTY(meta = (BindWidget))
    UButton* BTQuit;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Level)
    FString LevelName;

    UFUNCTION()
    void OnBTStartClicked();

    UFUNCTION()
    void OnBTQuitClicked();

    UFUNCTION(BlueprintImplementableEvent)
    void CreateSession();
};
