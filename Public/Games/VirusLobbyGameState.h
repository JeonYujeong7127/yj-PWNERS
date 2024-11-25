// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusGameState.h"
#include "VirusLobbyGameState.generated.h"

/**
 * Virus 프로젝트 로비 전용 게임 스테이트 클래스
 */
UCLASS()
class VIRUS_API AVirusLobbyGameState : public AVirusGameState
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    double ServerTime;

protected:
    UPROPERTY(Replicated = OnRep_bIsAllReady)
    bool bIsAllReady = false;

private:
    TArray<class AVirusLobbyPlayerController*> PCs;

public:
    /* Actor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */

    void EnterToStage();
    int8 StageNum = 0;

    void TimerStart();

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> LevelNames;

    bool bIsGameStart = false;

protected:
    /* 리플리케이트 */
    UFUNCTION()
    void OnRep_bIsAllReady();

    // Timer 관련

private:
    double StartTime;
    double EndTime;

    FTimerHandle GlobalHandle;
    FTimerHandle NormalHandle;
    FTimerHandle LoadingHandle;

    // 모두 준비된 후 지난 시간
    float PassedSecondAfterAllReady = 0.f;

    // 글로벌 타이머 기준 지난 시간
    float PassedSeconds = 0.f;

public:
    // 이 시간(초)이 지나면 준비가 안 됐어도 강제 이동
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float TimeOutSecond = 180.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    // 준비됐는지 체크하는 주기
    float CheckSecond = 1.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    // 모두 준비된 후 시작할 때까지 지나야 하는 시간
    float MustPassSecondAfterAllReady = 6.f;
};
