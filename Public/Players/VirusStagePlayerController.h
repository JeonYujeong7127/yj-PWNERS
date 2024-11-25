// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VirusPlayerController.h"
#include "VirusStagePlayerController.generated.h"

/**
 * Virus 프로젝트 스테이지 전용 플레이어 컨트롤러
 */
UCLASS()
class VIRUS_API AVirusStagePlayerController : public AVirusPlayerController
{
    GENERATED_BODY()

protected:
    // 스테이지 결과 표시를 위한 위젯 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> StageResultWidgetClass;

    // 위젯 인스턴스
    UPROPERTY(Transient)
    TObjectPtr<UUserWidget> StageResultWidget;

    // Die 상태를 알리는 위젯 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> DieWidgetClass;

    // 위젯 인스턴스
    UPROPERTY(Transient)
    TObjectPtr<UUserWidget> DieWidget;

public:
    /* Actor */
    virtual void BeginPlay() override;
    void ShowDieWidget();
    void RemoveDieWidget();

    UPROPERTY(ReplicatedUsing=OnRep_IsDie)
    bool bIsDie = false;

protected:
    // 스테이지 결과 이벤트 바인딩 메서드
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnStageResultReceived(const FStageResult& StageResult);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION()
    void OnRep_IsDie();
};
