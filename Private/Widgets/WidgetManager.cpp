// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WidgetManager.h"

#include "Blueprint/UserWidget.h"

// Sets default values
AWidgetManager::AWidgetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SetReplicates(true);
}

// Called when the game starts or when spawned
void AWidgetManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWidgetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWidgetManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


void AWidgetManager::MulticastShowWidgetFunction_Implementation(TSubclassOf<UUserWidget> UserWidget)
{
    UUserWidget* CreatedWidget = CreateWidget(GetWorld()->GetGameInstance(), UserWidget);
    CreatedWidget->AddToViewport();
}
