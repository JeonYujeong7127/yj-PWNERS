// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Weapon/CubeBossInstallation.h"

#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AI/AICharacter/CubeBossAI.h"
#include "GGFGameplayTags.h"
#include "Virus.h"
#include "AI/AIController/CubeBossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACubeBossInstallation::ACubeBossInstallation()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    RootComponent = StaticMeshComp; // Set RootComponent
}

void ACubeBossInstallation::BeginPlay()
{
	Super::BeginPlay();

    bReplicates = true;
    SetReplicateMovement(true);

    AddGameplayTag(State::Buff::Invinsible);

    Boss = Cast<ACubeBossAI>(GetOwner());

    if (HasAuthority())
    {
        ReplicatedLocation = GetActorLocation();
        ReplicatedRotation = GetActorRotation();

        StaticMeshNum = FMath::RandRange(0, 5);
        StaticMeshComp->SetStaticMesh(StaticMeshes[StaticMeshNum]);
        StaticMeshComp->SetSimulatePhysics(true);
    }
}

void ACubeBossInstallation::Destroyed()
{
    if (Boss)
    {
        UE_LOG(LogTemp, Log, TEXT("%s: Destroyed"), *GetName());
        Boss->InstallationDestroyed(this);

        // 마지막 Installation일 때, Heal을 멈추고 쿨타임 다운 시작
        if(InstallationNum == 5)
        {
            Boss->SetInvinsible(false);
            Boss->bIsHeal = false;
            Cast<ACubeBossAIController>(Boss->GetController())->SetIsAttacking(false);
            Cast<ACubeBossAIController>(Boss->GetController())->GetBlackboardComponent()->SetValueAsFloat(TEXT("PhantomRecoveryCooldown"), GetWorld()->GetTimeSeconds());
        }
    }
    Super::Destroyed();
}

void ACubeBossInstallation::AddGameplayTag(FGameplayTag Tag)
{
    if (GetAbilitySystemComponent())
    {
        GetAbilitySystemComponent()->AddReplicatedLooseGameplayTag(Tag);
        GetAbilitySystemComponent()->AddLooseGameplayTag(Tag);
    }
}

void ACubeBossInstallation::RemoveGameplayTag(FGameplayTag Tag)
{
    if (GetAbilitySystemComponent())
    {
        GetAbilitySystemComponent()->RemoveLooseGameplayTag(Tag);
        GetAbilitySystemComponent()->RemoveReplicatedLooseGameplayTag(Tag);
    }
}

void ACubeBossInstallation::OnRep_IsActivated()
{
    SetActivated(bIsActivated);
}

void ACubeBossInstallation::SetBoss(ACubeBossAI* CubeBoss)
{
    Boss = CubeBoss;
}

void ACubeBossInstallation::SetInstallationNum(int8 Num)
{
    InstallationNum = Num;
}

void ACubeBossInstallation::OnRep_StaticMeshNum()
{
    StaticMeshComp->SetStaticMesh(StaticMeshes[StaticMeshNum]);
}

// Called every frame
void ACubeBossInstallation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACubeBossInstallation::SetActivated(bool Value)
{
    if (StaticMeshComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s : Set Activated"), *GetName());

        if (Value)
        {
            StaticMeshComp->SetMaterial(0, GlowMaterial);
            RemoveGameplayTag(State::Buff::Invinsible);
        }
        else
        {
            StaticMeshComp->SetMaterial(0, nullptr);
            AddGameplayTag(State::Buff::Invinsible);
        }

        bIsActivated = Value;
    }
}

void ACubeBossInstallation::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ACubeBossInstallation, ReplicatedLocation);
    DOREPLIFETIME(ACubeBossInstallation, ReplicatedRotation);
    DOREPLIFETIME(ACubeBossInstallation, bIsActivated);
    DOREPLIFETIME(ACubeBossInstallation, StaticMeshNum);
}

void ACubeBossInstallation::OnRep_ReplcatedLocation()
{
    SetActorLocation(ReplicatedLocation);
}

void ACubeBossInstallation::OnRep_ReplicatedRotation()
{
    SetActorRotation(ReplicatedRotation);
}
