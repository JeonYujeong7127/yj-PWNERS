// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter/BossAIBase.h"

#include "GGFCombatGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "Games/VirusGameMode.h"
#include "Games/VirusGameState.h"

// Sets default values
ABossAIBase::ABossAIBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABossAIBase::BeginPlay()
{
	Super::BeginPlay();

    Health = MaxHealth;
}

void ABossAIBase::Die()
{
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}
