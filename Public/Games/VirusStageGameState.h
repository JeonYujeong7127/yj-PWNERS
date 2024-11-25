// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusGameState.h"
#include "VirusStageGameState.generated.h"

/**
 * 스테이지 결과 정보
 */
USTRUCT(BlueprintType, Blueprintable)
struct FStageResult
{
    GENERATED_BODY()

    // 스테이지 클리어 결과
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSucceed;

    double TotalTime;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageResultReceived, const FStageResult&, StageResult);

/**
 * Virus 프로젝트 스테이지 전용 게임 스테이트 클래스
 */
UCLASS()
class VIRUS_API AVirusStageGameState : public AVirusGameState
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void Destroyed() override;

    UPROPERTY(ReplicatedUsing=OnRep_bIsStageClear)
    bool bIsStageClear = false;

    UFUNCTION(BlueprintCallable)
    void SetIsStageClear(bool Value);

    UFUNCTION()
    void OnRep_bIsStageClear();

    UFUNCTION(BlueprintCallable)
    virtual void FinishGame(bool bResult);

    UFUNCTION()
    void FloatLoadingScreen();

    UFUNCTION()
    void FloatScript();

	TArray<class AVirusLobbyPlayerController*> PCs;

    FTimerHandle GameTimerHandle;

    FTimerHandle FinishTimerHandle;

    UPROPERTY(BlueprintAssignable)
    FOnStageResultReceived OnStageResultReceived;

    // 스테이지 시간 관련 변수
    double ServerTime;
    double StartTime;
    double EndTime;

    UPROPERTY()
    TMap<FString, UTexture2D*> SteamAvatars;

    /*// StageClearWidget.h
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (ExposeOnSpawn = "true"))
    class UMediaPlayer* MediaPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (ExposeOnSpawn = "true"))
    class UFileMediaSource* MediaSource;*/

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, ReplicatedUsing = OnRep_StageResult)
    FStageResult StageResult;

    UFUNCTION()
    void OnRep_StageResult();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION()
    virtual void ReturnToLobby();
};
