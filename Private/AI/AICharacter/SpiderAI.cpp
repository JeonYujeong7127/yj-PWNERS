// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter/SpiderAI.h"

#include "Virus.h"
#include "AI/AIController/AggressiveAIController.h"
#include "AI/Animation/AIAnimInstanceBase.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"

ASpiderAI::ASpiderAI()
{
    AIControllerClass = AAggressiveAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/Virus/Actors/AI/SpiderAI/ABP_SpiderAI.ABP_SpiderAI_C"));
    if (AnimInstanceRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
    }

    AIPatrolRadius = 1000.f;
    AIDetectRange = 400.f;
    AttackRange = 500.f;
    AttackTime = 0.6f;
    AttackRate = 20.f;

    AttackType = EAttackType::CloseSuicide;

    GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void ASpiderAI::BeginPlay()
{
    Super::BeginPlay();
    GetCharacterMovement()->MaxWalkSpeed = 200.f;

    AnimInstance = Cast<UAIAnimInstanceBase>(GetMesh()->GetAnimInstance());
}

void ASpiderAI::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    if(APawn* OtherPawn = Cast<APawn>(OtherActor)){
        if(OtherPawn->IsPlayerControlled())
        {
            if(CanAttack(OtherActor))
            {
                if(HasAuthority() || GetLocalRole()==ROLE_Authority)
                {
                    if(!bIsBomb)
                    {
                        FTimerHandle TimerHandle;
                        GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, OtherActor]
                        {
                            UE_LOG(LogTemp, Log, TEXT("%s 's AttackRate: %f"), *GetName(), AttackRate);

                            UGameplayStatics::ApplyDamage(OtherActor, AttackRate, GetController(), this, nullptr);

                            bIsBomb = true;
                            Bomb();
                        }), 0.5f, false);
                    }
                }
            }
        }
    }
}

void ASpiderAI::Bomb()
{
    // 자폭 로직
    FVector Location = GetActorLocation();

    AudioComponent->SetSound(BombSoundCue);
    AudioComponent->Play();
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, Location);
    this->SetActorHiddenInGame(true);

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
    {
        Destroy();
    }), 3.0f, false);
}

void ASpiderAI::OnRep_IsBomb()
{
    Bomb();
}

void ASpiderAI::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ASpiderAI, bIsBomb);
}
