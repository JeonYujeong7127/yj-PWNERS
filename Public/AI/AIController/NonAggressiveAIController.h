// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NonAggressiveAIController.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API ANonAggressiveAIController : public AAIController
{
    GENERATED_BODY()

public:
    ANonAggressiveAIController();
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    UPROPERTY(VisibleAnywhere, Category = AI)
    TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = AI)
    TObjectPtr<class UAISenseConfig_Damage> AISenseConfigDamage = nullptr;


protected:
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    // AI bt, bb 실행
    void RunAI();

    // AI bt, bb 중단
    void StopAI();

    // AI의 Perception 세팅
    void SetPerceptionConfig();

    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AISystem)
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AISystem)
    TObjectPtr<UBlackboardData> BBAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AISystem)
    TObjectPtr<UBehaviorTree> BTAsset;
};
