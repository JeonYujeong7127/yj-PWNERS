// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BossSpawner.h"

#include "AI/AICharacter/CubeBossAI.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABossSpawner::ABossSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
    BoxComponent->SetCollisionProfileName("OverlapOnlyPawn");
}

// Called when the game starts or when spawned
void ABossSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ABossSpawner::BossSpawn()
{
    if(BossReference)
    {
        Cast<ACubeBossAI>(BossReference)->SetAIActivated(true);
        bIsBossSpawned = true;
    }
}

void ABossSpawner::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if(!bIsBossSpawned && HasAuthority())
    {
        BossSpawn();
    }
}

// Called every frame
void ABossSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

