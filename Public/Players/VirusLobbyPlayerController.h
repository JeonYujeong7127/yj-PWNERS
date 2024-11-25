// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusPlayerController.h"
#include "VirusLobbyPlayerController.generated.h"

/**
 * Virus 프로젝트 로비 전용 플레이어 컨트롤러
 */
UCLASS()
class VIRUS_API AVirusLobbyPlayerController : public AVirusPlayerController
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    void TimerStart();

    void GameStart();
    void GameEnd();

    void FloatLoadingScreen();

    UPROPERTY()
    class UStageTimerWidget* StageTimerWidget;

    FTimerHandle StageTimerHandle;

    double ServerTime;
    double ClientTime;

    // 서버 전용 타이머 함수
    void TimerAllReady();
    void TimerNotReady();

    // 스테이지 타이머 함수
    void StageTimerStart();

    void ShowMainPlayWidget();

    bool bIsReady = false;

    UPROPERTY(ReplicatedUsing = OnRep_bIsLoading, Transient, VisibleInstanceOnly, Category = UI)
    bool bIsLoading = false;

    UPROPERTY(ReplicatedUsing = OnRep_bIsGameEnd, Transient, VisibleInstanceOnly, Category = UI)
    bool bIsGameEnd = false;

    UPROPERTY(ReplicatedUsing = OnRep_UserWidgetClass, Transient, VisibleInstanceOnly, Category = UI)
    TSubclassOf<UUserWidget> UserWidgetClass;

    UPROPERTY(ReplicatedUsing = OnRep_bIsTimerStart, Transient, VisibleInstanceOnly, Category = UI)
    bool bIsTimerStart = false;

    UPROPERTY(ReplicatedUsing = OnRep_bIsGameStart, Transient, VisibleInstanceOnly, Category = UI)
    bool bIsGameStart = false;

    UPROPERTY(ReplicatedUsing = OnRep_bIsAllReady, Transient, VisibleInstanceOnly, Category = UI)
    bool bIsAllReady = false;

    FTimerHandle ReadyTimer;

    int32 PassedTime = 0;

    UFUNCTION()
    void OnRep_bIsLoading();

    UFUNCTION()
    void OnRep_bIsGameEnd();

    UFUNCTION()
    void OnRep_UserWidgetClass();

    UFUNCTION()
    void OnRep_bIsTimerStart();

    UFUNCTION()
    void OnRep_bIsAllReady();

    UFUNCTION()
    void OnRep_bIsGameStart();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> LoadingWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> StageResultWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> LobbyTimerWidgetClass;

    UPROPERTY(Replicated)
    class UTimerWidget* TimerWidget;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> StageTimerWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> MainPlayerWidgetClass;

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
