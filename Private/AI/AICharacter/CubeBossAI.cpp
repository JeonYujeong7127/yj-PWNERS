#include "AI/AICharacter/CubeBossAI.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "GGFGameplayTags.h"
#include "Virus.h"
#include "Abilities/GGFGA_ApplyBuffToSelf.h"
#include "AI/AIController/CubeBossAIController.h"
#include "Components/CapsuleComponent.h"
#include "AI/Weapon/CubeBossBlock.h"
#include "AI/Weapon/CubeBossInstallation.h"
#include "AI/Weapon/Projectile.h"
#include "Attributes/GGFHealthAttributes.h"
#include "GameplayEffects/GGFGE_ContinuousHeal.h"
#include "GameplayEffects/GGFGE_Heal.h"
#include "Games/VirusStageGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

ACubeBossAI::ACubeBossAI()
{
    RootComponent = GetCapsuleComponent();

    OnAttackingStateChanged.AddDynamic(this, &ACubeBossAI::HandleAttackingStateChanged);
    MaxHealth = 30000.f;

    // 12번째 메시는 핵
    for (int32 i = 0; i < 11; ++i)
    {
        FString ComponentName = FString::Printf(TEXT("StaticMeshComponent_%d"), i);
        UStaticMeshComponent* NewComponent = CreateDefaultSubobject<UStaticMeshComponent>(*ComponentName);
        StaticMeshComponents.Add(NewComponent);

        NewComponent->SetupAttachment(RootComponent);
    }

    bReplicates = true;
    SetReplicatingMovement(true);
}

void ACubeBossAI::SetAIActivated(bool Value) const
{
    if(Value)
    {
        Cast<ACubeBossAIController>(GetController())->RunAI();
    }
}

void ACubeBossAI::CoreBoom()
{
    if (HasAuthority())
    {
        StartRising();
        SetInvinsible(true);
    }
}

void ACubeBossAI::Heal()
{
    if (AbilitySystemComponent && IsValid(UGGFGE_Heal::StaticClass()))
    {
        if (UGGFGE_Heal* HealGameplayEffect = NewObject<UGGFGE_Heal>(GetTransientPackage(), FName("GGFGE_Heal")))
        {
            HealGameplayEffect->SetHealMagnitude(0.1f); // 0.1f 크기의 힐 량 설정
            AbilitySystemComponent->ApplyGameplayEffectToSelf(HealGameplayEffect, 1, AbilitySystemComponent->MakeEffectContext());
        }
    }
}

void ACubeBossAI::SetInvinsible(bool Value)
{
    if (HasAuthority())
    {
        if (GetAbilitySystemComponent())
        {
            if (Value)
            {
                GetAbilitySystemComponent()->AddLooseGameplayTag(State::Buff::Invinsible);
                GetAbilitySystemComponent()->AddReplicatedLooseGameplayTag(State::Buff::Invinsible);
            }
            else
            {
                GetAbilitySystemComponent()->RemoveLooseGameplayTag(State::Buff::Invinsible);
                GetAbilitySystemComponent()->RemoveReplicatedLooseGameplayTag(State::Buff::Invinsible);
            }
        }
    }
}

void ACubeBossAI::SetDamageable(bool Value)
{
    if (HasAuthority())
    {
        bIsDamageable = Value;
    }
}

void ACubeBossAI::AddInstallation(ACubeBossInstallation* Installation)
{
    if (HasAuthority())
    {
        Installations.Add(Installation);
    }
}

void ACubeBossAI::ActivateNextInstallation()
{
    if (HasAuthority() && Installations.IsValidIndex(CurrentInstallationIndex))
    {
        Installations[CurrentInstallationIndex]->SetActivated(true);
    }
}

void ACubeBossAI::InstallationDestroyed(ACubeBossInstallation* DestroyedInstallation)
{
    if (HasAuthority())
    {
        DestroyedInstallation->SetActivated(false);
        ++CurrentInstallationIndex;
        ActivateNextInstallation();
    }
}

void ACubeBossAI::PhantomRecoveryInstall()
{
    if (HasAuthority())
    {
        SetInvinsible(true);

        bIsHeal = true;
        if (UWorld* World = GetWorld())
        {
            SetActorLocation(InitLocation);
            FVector BossLocation = GetActorLocation();
            for (int32 i = 0; i < 6; ++i)
            {
                FVector RandomLocation = BossLocation + UKismetMathLibrary::RandomUnitVector() * FMath::RandRange(1000.f, 1800.f);
                RandomLocation = FVector(RandomLocation.X, RandomLocation.Y, 4700);

                const float Pitch = FMath::FRandRange(-180.f, 180.f);
                const float Yaw = FMath::FRandRange(-180.f, 180.f);
                const float Roll = FMath::FRandRange(-180.f, 180.f);

                FRotator Rotation = FRotator(Pitch, Yaw, Roll);

                FTransform SpawnTransform;
                SpawnTransform.SetLocation(RandomLocation);
                SpawnTransform.SetRotation(Rotation.Quaternion());

                if (ACubeBossInstallation* Installation = World->SpawnActor<ACubeBossInstallation>(InstallationClass, SpawnTransform))
                {
                    Installation->SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
                    Installation->SetBoss(this);
                    Installation->SetInstallationNum(i);

                    Installation->ReplicatedLocation = RandomLocation;
                    Installation->ReplicatedRotation = Rotation;

                    AddInstallation(Installation);
                }
            }
        }
        ActivateNextInstallation();
    }
}

void ACubeBossAI::SpinOfDestructionFire()
{
    if (HasAuthority())
    {
        GetWorld()->GetTimerManager().SetTimer(FireHandle, FTimerDelegate::CreateLambda([this]
        {
            if(this->IsValidLowLevel())
            {
                if (FireCount >= 8)
                {
                    GetWorld()->GetTimerManager().ClearTimer(FireHandle);
                    FireCount = 0;
                }
                else
                {
                    for (int32 i = 0; i < 16; ++i)
                    {
                        if(IsValid(this))
                        {
                            float Angle = FMath::DegreesToRadians(i * 22.5f);
                            FVector Direction = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0);

                            FTransform SpawnTransform;
                            SpawnTransform.SetLocation(GetActorLocation() + FVector(0, 0, 300));
                            SpawnTransform.SetRotation(FRotator(Direction.Rotation().Pitch, Direction.Rotation().Yaw + FireCount * 10.f, Direction.Rotation().Roll).Quaternion());

                            if (AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnTransform))
                            {
                                Projectile->InitializeProjectile(Direction);
                                Projectile->SetBossAIController(this);
                            }
                        }
                        else
                        {
                            GetWorld()->GetTimerManager().ClearTimer(FireHandle);
                            return;
                        }
                    }

                    FireCount++;
                }
            }
        }), 1.0f, true);
    }
}

void ACubeBossAI::SetStaticMeshToRoot()
{
    for (auto StaticMeshComponent : StaticMeshComponents)
    {
        StaticMeshComponent->SetupAttachment(RootComponent);
    }
}

void ACubeBossAI::HideAndSpawnActor(UStaticMeshComponent* StaticMesh, const FVector& SpawnTargetLocation)
{
    StaticMesh->SetVisibility(false, true);

    if (HasAuthority() && StaticMesh)
    {
        FVector Location = StaticMesh->GetComponentLocation();

        const float pitch = FMath::FRandRange(-180.f, 180.f);
        const float yaw = FMath::FRandRange(-180.f, 180.f);
        const float roll = FMath::FRandRange(-180.f, 180.f);

        FRotator Rotation = FRotator(pitch, yaw, roll);

        FTransform Transform = FTransform(Rotation.Quaternion(), SpawnTargetLocation, FVector(0.2f, 0.2f, 0.2f));

        if (ACubeBossBlock* Block = GetWorld()->SpawnActor<ACubeBossBlock>(BlockClass, Transform))
        {
            if (UStaticMeshComponent* SpawnedStaticMeshComponent = Block->FindComponentByClass<UStaticMeshComponent>())
            {
                Block->ReplicatedStaticMesh = StaticMesh->GetStaticMesh();

                SpawnedStaticMeshComponent->SetStaticMesh(StaticMesh->GetStaticMesh());
                SpawnedStaticMeshComponent->SetWorldScale3D(StaticMesh->GetComponentScale());
                SpawnedStaticMeshComponent->SetSimulatePhysics(true);
            }
            SpawnedActors.Add(Block);
        }

        if(this)
        {
            // 타이머 설정
            TWeakObjectPtr<AActor> WeakThis(this);

            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis, StaticMesh]
            {
                if(WeakThis.IsValid())
                {
                    ACubeBossAI* This = Cast<ACubeBossAI>(WeakThis.Get());
                    for (auto StaticMeshComponent : This->StaticMeshComponents)
                    {
                        This->ShowOriginalStaticMesh(StaticMesh);
                    }

                    for (auto t : This->SpawnedActors)
                    {
                        t->Destroy();
                    }
                    This->SpawnedActors.Empty();
                }
            }), 10.0f, false);
        }
    }
}

void ACubeBossAI::ShowOriginalStaticMesh(UStaticMeshComponent* StaticMesh)
{
    if (HasAuthority() && StaticMesh)
    {
        StaticMesh->SetVisibility(true, true);
        StaticMesh->SetSimulatePhysics(false);

        if (SpawnedActor)
        {
            SpawnedActor->Destroy();
        }
    }
}

void ACubeBossAI::StartRising()
{
    if (HasAuthority())
    {
        LaunchCharacter(FVector(0, 0, 2000.f), false, false);

        FTimerHandle RiseTimerHandle;
        GetWorldTimerManager().SetTimer(RiseTimerHandle, FTimerDelegate::CreateLambda([this]
        {
            LaunchCharacter(FVector(0, 0, -7000.f), false, false);
            GetCapsuleComponent()->SetCapsuleHalfHeight(0);
        }), 3.f, false);

        FTimerHandle CapsuleTimerHandle;
        GetWorldTimerManager().SetTimer(CapsuleTimerHandle, FTimerDelegate::CreateLambda([this]
        {
            DealDamage();

            GetCapsuleComponent()->SetCapsuleHalfHeight(200.f);
            SetInvinsible(false);
        }), 3.5f, false);
    }
}

void ACubeBossAI::StartFalling()
{

}

void ACubeBossAI::DealDamage()
{
    if (HasAuthority())
    {
        UE_LOG(LogTemp, Log, TEXT("Deal!"));

        FVector ActorLocation = GetActorLocation();
        TArray<AActor*> OverlappingActors;
        float DamageRadius = 5000.0f;

        UGameplayStatics::ApplyRadialDamage(
            GetWorld(),
            30.0f,
            ActorLocation,
            DamageRadius,
            nullptr,
            OverlappingActors,
            this,
            GetInstigatorController(),
            true
        );
    }
}

void ACubeBossAI::OnDead_Implementation()
{
    Super::OnDead_Implementation();

    Cast<ACubeBossAIController>(GetController())->StopAI();
    Cast<AVirusStageGameState>(GetWorld()->GetGameState())->SetIsStageClear(true);

    Destroy();

    /*
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
    {
        Destroy();
    }), 30.f, false);
    */
}

void ACubeBossAI::BeginPlay()
{
    Super::BeginPlay();

    RootComponent = GetCapsuleComponent();
    InitLocation = GetActorLocation();
    AbilitySystemComponent = GetAbilitySystemComponent();
    Attribute = UGGFHealthAttributes::GetHealthAttribute();
}

void ACubeBossAI::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    bool bFound;
    Health = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bFound);

    if (bIsSpinning)
    {
        AddActorLocalRotation(FRotator(0, 1, 0));
    }
    if (bIsHeal)
    {
        if(Health >= 1500)
        {
            bIsHeal = false;
        }
        Heal();
    }
}

void ACubeBossAI::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
    FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    if (APawn* OtherPawn = Cast<APawn>(Other))
    {
        if (OtherPawn->IsPlayerControlled())
        {
            if (bIsDamageable)
            {
                if (HasAuthority())
                {
                    UGameplayStatics::ApplyDamage(Other, 20.f, GetController(), this, nullptr);
                    bIsDamageable = false;
                }

            }
        }
    }
}

void ACubeBossAI::HandleAttackingStateChanged(bool bNewIsAttacking)
{
    if (HasAuthority())
    {
        UE_LOG(LogTemp, Log, TEXT("Attacking state changed: %s"), bNewIsAttacking ? TEXT("True") : TEXT("False"));
    }
}

void ACubeBossAI::OnRep_IsAttacking()
{
    OnAttackingStateChanged.Broadcast(bIsAttacking);
}

void ACubeBossAI::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ACubeBossAI, bIsAttacking);
}
