// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Weapon/CubeBossBlock.h"

#include "Virus.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"

// Sets default values
ACubeBossBlock::ACubeBossBlock()
{
	PrimaryActorTick.bCanEverTick = true;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    RootComponent = StaticMeshComponent;

    StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    bReplicates = true;

    Damage = 10.f;
}

void ACubeBossBlock::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    UE_LOG(LogTemp, Log, TEXT("notifyactorbeginoverlap %s with %s"), *GetName(), *OtherActor->GetName());

    if (bIsFalling && OtherActor && OtherActor != this)
    {
        // Check if the other actor is a player
        APawn* OtherPawn = Cast<APawn>(OtherActor);
        if (OtherPawn && OtherPawn->IsPlayerControlled())
        {
            // Apply damage to the player
            UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
        }
        else
        {
            UGameplayStatics::PlaySoundAtLocation(this, FallingSoundCue, GetActorLocation(), 1.f, 1.f, 0.3f);
        }

        bIsFalling = false;
    }
}

void ACubeBossBlock::OnRep_StaticMesh()
{
    StaticMeshComponent->SetStaticMesh(ReplicatedStaticMesh);
}

void ACubeBossBlock::BeginPlay()
{
	Super::BeginPlay();

    bIsFalling = true;
    bReplicates = true;

    SetReplicateMovement(true);

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
    {
        bIsFalling = false;
    }), 3.f, false);
}

void ACubeBossBlock::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void ACubeBossBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACubeBossBlock::OnRep_ReplicatedTransform()
{
    SetActorTransform(ReplicatedTransform);
}

void ACubeBossBlock::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ACubeBossBlock, bIsFalling)
    DOREPLIFETIME(ACubeBossBlock, ReplicatedTransform)
    DOREPLIFETIME(ACubeBossBlock, ReplicatedStaticMesh)
}

