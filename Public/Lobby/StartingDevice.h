// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFInteractableMenuActor.h"
#include "StartingDevice.generated.h"

/**
 * 로비에서 스테이지를 선택하여 게임을 시작하기 위한 오브젝트입니다.
 * 상호작용을 통해 스테이지 선택 UI를 화면에 띄울 수 있습니다.
 */
UCLASS()
class VIRUS_API AStartingDevice : public AGGFInteractableMenuActor
{
    GENERATED_BODY()

public:
    AStartingDevice();
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* DisplayMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* BigDisplayMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* Display_Stage1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* Display_Stage2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* Display_None;

    void SettingDisplay(int32 Num);

    UPROPERTY(ReplicatedUsing=OnRep_IsStageNumChanged)
    int32 StageNum = 0;

    UFUNCTION()
    void OnRep_IsStageNumChanged();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
