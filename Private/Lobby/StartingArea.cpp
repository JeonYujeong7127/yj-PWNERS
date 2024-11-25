// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/StartingArea.h"

#include "Players/VirusLobbyPlayerController.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Controller.h"

// Sets default values
AStartingArea::AStartingArea()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
    CollisionBox->AttachToComponent(StaticMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Collision Box"));
}

// Called when the game starts or when spawned
void AStartingArea::BeginPlay()
{
    Super::BeginPlay();

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStartingArea::BeginOverlap);
    CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AStartingArea::EndOverlap);
}

// Called every frame
void AStartingArea::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AStartingArea::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(Cast<APawn>(OtherActor))
    {
        if(Cast<AVirusLobbyPlayerController>(Cast<APawn>(OtherActor)->GetController()))
        {
            Cast<AVirusLobbyPlayerController>(Cast<APawn>(OtherActor)->GetController())->bIsReady = true;
        }
    }
}

void AStartingArea::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if(Cast<APawn>(OtherActor))
    {
        if(Cast<AVirusLobbyPlayerController>(Cast<APawn>(OtherActor)->GetController()))
        {
            Cast<AVirusLobbyPlayerController>(Cast<APawn>(OtherActor)->GetController())->bIsReady = false;
        }
    }
}

