// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter/ArmWheelAI.h"

#include "AI/AIController/AggressiveAIController.h"
#include "AI/Animation/AIAnimInstanceBase.h"
#include "GameFramework/CharacterMovementComponent.h"

AArmWheelAI::AArmWheelAI()
{
    AIControllerClass = AAggressiveAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/Virus/Actors/AI/ArmWheelAI/ABP_ArmWheelAI.ABP_ArmWheelAI_C"));
    if (AnimInstanceRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
    }

    AIPatrolRadius = 500.f;
    AIDetectRange = 400.f;
    AttackRange = 300.f;
    AttackTime = 2.f;
    AttackRate = 40.f;

    AttackType = EAttackType::CloseWheelWind;

    GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void AArmWheelAI::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = 150.f;

    AnimInstance = Cast<UAIAnimInstanceBase>(GetMesh()->GetAnimInstance());
}
