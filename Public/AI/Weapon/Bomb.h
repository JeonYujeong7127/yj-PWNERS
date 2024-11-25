// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class VIRUS_API ABomb : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
    ABomb();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovementComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UParticleSystem* ParticleSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USoundCue* BombSoundCue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual void Bomb(AActor* OtherActor);

    UPROPERTY()
    AActor* TargetActor;

    UPROPERTY()
    class UStaticMesh* Sphere;

    UPROPERTY()
    class UAudioComponent* AudioComponent;

    UPROPERTY(ReplicatedUsing=OnRep_IsBomb, BlueprintReadOnly)
    bool bIsBomb = false;

    UFUNCTION()
    void OnRep_IsBomb();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
