// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter/VirusAIBase.h"

#include "Virus.h"
#include "AbilitySystem/GGFDamageableAbilitySystem.h"
#include "AI/AIController/AggressiveAIController.h"
#include "AI/Animation/AIAnimInstanceBase.h"
#include "AI/Weapon/Bomb.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/GGFGameplayStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"

AVirusAIBase::AVirusAIBase()
{
    bReplicates = true;

    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_NavWalking);
    AttackRangeCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("AttackRange");
    AttackRangeCapsuleComponent->SetupAttachment(RootComponent);

    AttackCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("AttackCollision");
    AttackCapsuleComponent->SetupAttachment(RootComponent);

    AttackCapsuleComponent->SetCapsuleRadius(20.f);
    AttackCapsuleComponent->SetCapsuleHalfHeight(20.f);

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->bAutoActivate = false;

    /* DamageableAbilitySystem */
    if(auto DamageableAbilitySystem = Cast<UGGFDamageableAbilitySystem>(GetAbilitySystem()))
    {
        DamageableAbilitySystem->MaxHealth = 1000;
    }
}

void AVirusAIBase::BeginPlay()
{
    Super::BeginPlay();

    GetMesh()->SetCollisionProfileName("CharacterMesh");

    AttackCapsuleComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("AttackCollision"));
    AttackCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AVirusAIBase::OnOverlapBeginInAttackCollisionCapsule);

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

    AttackRangeCapsuleComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform);

    AttackRangeCapsuleComponent->SetCapsuleRadius(AttackRange);
    AttackRangeCapsuleComponent->SetCapsuleHalfHeight(AttackRange);

    AttackRangeCapsuleComponent->SetCollisionProfileName("OverlapAll");
    AttackRangeCapsuleComponent->SetGenerateOverlapEvents(true);

    AttackRangeCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AVirusAIBase::OnOverlapBeginInAttackCapsule);
    AttackRangeCapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &AVirusAIBase::OnOverlapEndInAttackCapsule);
}

bool AVirusAIBase::CanAttack(AActor* PlayerActor)
{
    FVector Start = GetActorLocation();
    FVector End = PlayerActor->GetActorLocation();

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this); // AI 자신을 무시

    // 라인 트레이스 실행
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

    if (bHit && HitResult.GetActor() == PlayerActor)
    {
        UE_LOG(LogTemp, Log, TEXT("HitResult.GetActor : %s, PlayerActor : %s"), *HitResult.GetActor()->GetName(), *PlayerActor->GetName());
        return true;
    }
    else return false;
}

void AVirusAIBase::PlayAttackSound()
{
    UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
}

void AVirusAIBase::OnOverlapBeginInAttackCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(HasAuthority())
    {

        if(APawn* OtherPawn = Cast<APawn>(OtherActor))
        {
            if(OtherPawn->IsPlayerControlled())
            {
                if(!bIsPlayerInAttackRange)
                {
                    bIsPlayerInAttackRange = true;
                    TargetPlayerInAttackRange = OtherPawn;

                    Cast<AAggressiveAIController>(GetController())->SetTargetInAttackRange(OtherPawn);
                }
            }
        }
    }
}

void AVirusAIBase::OnOverlapEndInAttackCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if(APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        if(OtherPawn->IsPlayerControlled())
        {
            bIsPlayerInAttackRange = false;
            TargetPlayerInAttackRange = nullptr;
        }
    }
}

void AVirusAIBase::OnOverlapBeginInAttackCollisionCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(bIsAttacking)
    {
        if(ACharacter* Character = Cast<ACharacter>(OtherActor))
        {
            if(Character->IsPlayerControlled())
            {
                UGameplayStatics::ApplyDamage(OtherActor, AttackRate, GetController(), this, nullptr);
            }
        }
    }
}

void AVirusAIBase::OnRep_IsAttacking()
{
    if(HasAuthority())
    {
        Cast<AAggressiveAIController>(GetController())->SetIsAttacking(bIsAttacking);
    }
}

void AVirusAIBase::OnDead_Implementation()
{
    if(!AnimInstance) return;

    AnimInstance->bIsDie = true;

    if(HasAuthority())
    {
        Cast<AAggressiveAIController>(GetController())->StopAI();
    }
    GetMesh()->SetSimulatePhysics(false);

    FTimerHandle DestroyHandle;
    GetWorld()->GetTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([&]
    {
        Destroy();
    }), 4.f, false);

    Super::OnDead_Implementation();
}

void AVirusAIBase::BulletAttack(APawn* TargetPawn)
{
    if(ProjectileClass)
    {
        const FTransform ActorTransform = GetActorTransform();
        const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters();

        AActor* ProjectileActor = GetWorld()->SpawnActor(ProjectileClass, &ActorTransform, SpawnParameters);

        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([ProjectileActor]
        {
            ProjectileActor->Destroy();
        }), AttackTime, false);
    }
}

void AVirusAIBase::BombAttack(APawn* TargetPawn)
{
    // 공격 로직
    if(TargetPawn)
    {
        const FTransform Transform = TargetPawn->GetTransform();
        const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters();

        GetWorld()->SpawnActor(ABomb::StaticClass(), &Transform, SpawnParameters);

        FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 50);
        FVector PlayerLocation = TargetPawn->GetActorLocation();
        FVector Direction = PlayerLocation - SpawnLocation;
        Direction.Normalize();

        // 발사 각도 계산
        float LaunchAngle = 20.0f;
        float LaunchSpeed = 700.0f;
        float RadAngle = FMath::DegreesToRadians(LaunchAngle);
        FVector LaunchVelocity = Direction * LaunchSpeed * FMath::Cos(RadAngle);
        LaunchVelocity.Z = LaunchSpeed * FMath::Sin(RadAngle);

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = this->GetInstigator();

        // 폭탄 생성
        ABomb* Bomb = GetWorld()->SpawnActor<ABomb>(BombClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
        if (Bomb)
        {
            // 폭탄 발사
            Bomb->SetOwner(this);
            Bomb->ProjectileMovementComponent->Velocity = LaunchVelocity;
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Target Not Found"));
    }
}

void AVirusAIBase::ArmAttack(APawn* TargetPawn)
{
    // 공격 로직
}

void AVirusAIBase::WheelWindAttack(TArray<AActor*> Targets)
{
    for(auto Target : Targets)
    {
        if(Cast<ACharacter>(Target))
        {
         // 공격 로직
        }
    }
}

void AVirusAIBase::SuicideAttack(APawn* TargetPawn)
{
    if(TargetPawn)
    {
        FVector LaunchVector = FVector(TargetPawn->GetActorLocation() - GetActorLocation());
        LaunchVector += FVector(0, 0, 300.f);
        this->LaunchCharacter(LaunchVector, true, true);
    }
}

void AVirusAIBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AVirusAIBase, bIsAttacking);
}
