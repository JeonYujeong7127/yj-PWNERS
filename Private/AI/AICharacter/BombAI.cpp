// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter/BombAI.h"

#include "AI/AIController/AggressiveAIController.h"
#include "AI/Animation/AIAnimInstanceBase.h"
#include "GameFramework/CharacterMovementComponent.h"

ABombAI::ABombAI()
{
    AIControllerClass = AAggressiveAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/Virus/Actors/AI/BombAI/ABP_BombAI.ABP_BombAI_C"));
    if (AnimInstanceRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
    }

    AIPatrolRadius = 1000.f;
    AIDetectRange = 400.f;
    AttackTime = 0.8f;
    WalkSpeed = 300.f;

    AttackType = EAttackType::FarBomb;

    GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void ABombAI::BeginPlay()
{
    Super::BeginPlay();

    AnimInstance = Cast<UAIAnimInstanceBase>(GetMesh()->GetAnimInstance());
}
