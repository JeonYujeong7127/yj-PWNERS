// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossSpawner.generated.h"

UCLASS()
class VIRUS_API ABossSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABossSpawner();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UBoxComponent* BoxComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UClass* BossClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> BossReference;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void BossSpawn();

    bool bIsBossSpawned = false;

    UFUNCTION()
    void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
