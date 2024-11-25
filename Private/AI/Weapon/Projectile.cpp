// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Weapon/Projectile.h"

#include "AI/AIController/CubeBossAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    ParticleEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleEffectComponent"));
    ParticleEffectComponent->SetupAttachment(RootComponent);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = ParticleEffectComponent;
    ProjectileMovement->InitialSpeed = 2000.f;
    ProjectileMovement->MaxSpeed = 2000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;

    RootComponent = ParticleEffectComponent;
}

void AProjectile::InitializeProjectile(FVector Direction)
{
    ProjectileDirection = Direction;
}

void AProjectile::SetBossAIController(APawn* Boss)
{
    CubeBossAIController = Cast<ACubeBossAIController>(Boss->GetController());
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

    if (ParticleEffect)
    {
        ParticleEffectComponent->SetTemplate(ParticleEffect);
        ParticleEffectComponent->ActivateSystem();
    }
}

void AProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
    FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    if(Cast<ACharacter>(Other)->IsPlayerControlled())
    {
        UGameplayStatics::ApplyDamage(Other, 10.f, CubeBossAIController, this, nullptr);
    }

    Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

