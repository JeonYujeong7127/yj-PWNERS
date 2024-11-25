// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter/NonAggressiveAI.h"
#include "AI/AIController/NonAggressiveAIController.h"

ANonAggressiveAI::ANonAggressiveAI()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    AIControllerClass = ANonAggressiveAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    AIPatrolRadius = 500.f;
    AIDetectRange = 400.f;
    AttackRange = 100.f;
}
