// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "AINavMeshBoundsVolume.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API AAINavMeshBoundsVolume : public ANavMeshBoundsVolume
{
	GENERATED_BODY()

public:
    AAINavMeshBoundsVolume();
    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

    void FindPlayer();

    UPROPERTY()
    TArray<class AVirusAIBase*> AIs;
};
