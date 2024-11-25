// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AggressiveAIController.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API AAggressiveAIController : public AAIController
{
	GENERATED_BODY()

public:
    AAggressiveAIController();
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    virtual void SetTargetInAttackRange(APawn* Target);
    virtual void SetIsAttacking(bool Value);

    UPROPERTY(VisibleAnywhere, Category = AI)
    TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = AI)
    TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    TObjectPtr<class UBlackboardData> BlackboardData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    TObjectPtr<class UBehaviorTree> BehaviorTree;

    // 현재 NavMesh에 있는 플레이어들
    UPROPERTY()
    TArray<APawn*> PlayersInNavMesh;

    // AI bt, bb 중단
    void StopAI();


protected:
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    void SetbIsPlayerInPatrol(bool bIsPlayerInPatrol);

    // AI bt, bb 실행
    void RunAI();


    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AISystem)
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AISystem)
    TObjectPtr<UBlackboardData> BBAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AISystem)
    TObjectPtr<UBehaviorTree> BTAsset;
};
