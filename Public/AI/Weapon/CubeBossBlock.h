// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeBossBlock.generated.h"

UCLASS()
class VIRUS_API ACubeBossBlock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACubeBossBlock();

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USoundCue* FallingSoundCue;

    UPROPERTY(ReplicatedUsing=OnRep_StaticMesh)
    UStaticMesh* ReplicatedStaticMesh;

    UFUNCTION()
    void OnRep_StaticMesh();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(ReplicatedUsing=OnRep_ReplicatedTransform)
    FTransform ReplicatedTransform;

private:
    UPROPERTY(Replicated)
    bool bIsFalling = true;

    UFUNCTION()
    void OnRep_ReplicatedTransform();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
