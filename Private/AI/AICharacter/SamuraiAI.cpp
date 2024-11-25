// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter/SamuraiAI.h"

#include "AI/AIController/AggressiveAIController.h"
#include "AI/Animation/AIAnimInstanceBase.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"

ASamuraiAI::ASamuraiAI()
{
    /* 기본 설정 */
    AIControllerClass = AAggressiveAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIPatrolRadius = 1000.f;
    AIDetectRange = 400.f;
    AttackRange = 200.f;
    AttackTime = 1.5f;
    AttackRate = 20.f;
    AttackType = EAttackType::CloseArmAttack;

    /* CharacterMovement */
    GetCharacterMovement()->SetMovementMode(MOVE_Walking);

    /* WeaponMesh */
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(GetMesh());

    /* 기본 에셋 설정 */
    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/Virus/Actors/AI/SamuraiAI/ABP_SamuraiAI.ABP_SamuraiAI_C"));
    if (AnimInstanceRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
    }
}

void ASamuraiAI::BeginPlay()
{
    Super::BeginPlay();

    AttackCapsuleComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_R"));
    WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_R"));

    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    AnimInstance = Cast<UAIAnimInstanceBase>(GetMesh()->GetAnimInstance());
}
