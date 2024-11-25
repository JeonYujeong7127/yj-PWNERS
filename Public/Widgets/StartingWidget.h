// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/GGFInteractionMenuWidget.h"
#include "StartingWidget.generated.h"

// TODO 스테이지 이동 관련 기능은 GameMode 혹은 StageManager 클래스로 이전하는 것이 좋을 것 같습니다.
// TODO UI는 다른 클래스의 메서드 호출을 위젯과 바인딩해주는 역할일 뿐 UI와 관련없는 기능을 직접 구현하는 것은 바람직하지 않을 것 같습니다.
/**
 * 스테이지 선택 UI
 */
UCLASS()
class VIRUS_API UStartingWidget : public UGGFInteractionMenuWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Level)
    FString LevelName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> TimerWidgetClass;


protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* BTStart;

    UPROPERTY(meta = (BindWidget))
    class UButton* BTStage1;

    UPROPERTY(meta = (BindWidget))
    class UButton* BTStage2;

    UPROPERTY(meta = (BindWidget))
    class UButton* BTStage3;


private:
    UFUNCTION()
    void OnBTStartClicked();

    UFUNCTION()
    void OnBTStage1Clicked() { StageNum = 1; };

    UFUNCTION()
    void OnBTStage2Clicked() { StageNum = 2; };

    UFUNCTION()
    void OnBTStage3Clicked() { StageNum = 3; };

    UPROPERTY()
    class UTimerWidget* TimerWidget;

    int32 StageNum = 0;
};
