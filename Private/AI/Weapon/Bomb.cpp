// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Weapon/Bomb.h"

#include "AI/AINavMeshBoundsVolume.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"

// Sets default values
ABomb::ABomb()
{
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->InitSphereRadius(15.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
    RootComponent = CollisionComponent;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    ProjectileMovementComponent->InitialSpeed = 1000.0f;
    ProjectileMovementComponent->MaxSpeed = 1000.0f;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true;

    bReplicates = true;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

    bReplicates = true;
    SetReplicateMovement(true);
}

void ABomb::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    if(HasAuthority())
    {
        if(!bIsBomb){
            if(!Cast<AVirusAIBase>(OtherActor) && !Cast<AAINavMeshBoundsVolume>(OtherActor))
            {
                UE_LOG(LogTemp, Log, TEXT("OtherActor :%s"), *OtherActor->GetName());
                TargetActor = OtherActor;
                bIsBomb = true;
                Bomb(OtherActor);
            }
        }
    }
}

void ABomb::Bomb(AActor* OtherActor)
{
    if(APawn* OwnerPawn = Cast<APawn>(GetOwner()))
    {
        UGameplayStatics::ApplyDamage(OtherActor, 20.f, Cast<APawn>(GetOwner())->GetController(), this, nullptr);
    }

    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation(), GetActorRotation());
    AudioComponent->SetSound(BombSoundCue);
    AudioComponent->Play();

    this->SetActorHiddenInGame(true);
}

void ABomb::OnRep_IsBomb()
{
    Bomb(TargetActor);
}

void ABomb::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ABomb, bIsBomb);
}
