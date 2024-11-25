// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartingArea.generated.h"

UCLASS()
class VIRUS_API AStartingArea : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AStartingArea();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category ="ActorMeshComponents")
    UStaticMeshComponent* StaticMesh;

    UPROPERTY(VisibleAnywhere,Category ="ActorMeshComponents")
    class UBoxComponent* CollisionBox;

private:
    UFUNCTION()
    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

    UFUNCTION()
    void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
