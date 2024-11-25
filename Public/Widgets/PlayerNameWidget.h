// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerNameWidget.generated.h"

class UTextBlock;

/**
 * 캐릭터 머리 위에 플레이어 이름 표시를 위한 위젯 클래스
 */
UCLASS()
class VIRUS_API UPlayerNameWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> PlayerNameText;

public:
    UFUNCTION(BlueprintCallable)
    virtual void SetPlayerName(FString NewPlayerName);
};
