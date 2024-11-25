// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class VIRUS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();
    void InitializeProjectile(FVector Direction);

    UPROPERTY()
    class ACubeBossAIController* CubeBossAIController;

    void SetBossAIController(APawn* Boss);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* ParticleEffect;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* ParticleEffectComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovement;

    UFUNCTION()
    void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

    FVector ProjectileDirection;
    float Speed;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
