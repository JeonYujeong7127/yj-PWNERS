// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AICharacter/AggressiveAI.h"
#include "AI/AIController/AggressiveAIController.h"
#include "AI/Animation/AIAnimInstanceBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAggressiveAI::AAggressiveAI()
{
	PrimaryActorTick.bCanEverTick = false;

    AIControllerClass = AAggressiveAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    GetCharacterMovement()->SetMovementMode(MOVE_Walking);

    ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/ParagonBelica/Characters/Heroes/Belica/Skins/Biohazard/Meshes/Belica_Biohazard.Belica_Biohazard"));
    if(MeshRef.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(MeshRef.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/Virus/Actors/AI/AggresiveAI/ABP_AggressiveAI.ABP_AggressiveAI_C"));
    if (AnimInstanceRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
    }

    // AI 디폴트 설정 (각 자식 클래스에서 재정의)
    AIPatrolRadius = 500.f;
    AIDetectRange = 400.f;
    AttackRange = 100.f;
    AttackTime = 1.f;
}

// Called when the game starts or when spawned
void AAggressiveAI::BeginPlay()
{
	Super::BeginPlay();
    AnimInstance = Cast<UAIAnimInstanceBase>(GetMesh()->GetAnimInstance());

    GetCharacterMovement()->MaxWalkSpeed = 300.f;
}
