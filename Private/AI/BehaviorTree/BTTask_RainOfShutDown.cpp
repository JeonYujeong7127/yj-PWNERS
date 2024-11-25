// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTTask_RainOfShutDown.h"

#include "AIController.h"
#include "AI/AICharacter/CubeBossAI.h"
#include "AI/AIController/CubeBossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RainOfShutDown::UBTTask_RainOfShutDown()
{
    NodeName = TEXT("Rain of Shutdown");

    CooldownDuration = 5.0f; // Default cooldown duration
    CooldownKey = "RainOfShutdownCooldown";
}

EBTNodeResult::Type UBTTask_RainOfShutDown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // 15 미터 이내에 플레이어가 있을 경우에만 HyperRush 실행
    if(BlackboardComp->GetValueAsFloat(TEXT("DistanceToPlayer")) > 1500.f)
    {
        UE_LOG(LogTemp, Log, TEXT("player is too far: %f"), BlackboardComp->GetValueAsFloat(TEXT("DistanceToPlayer")));
        return EBTNodeResult::Failed;
    }

    // Perform the Rain of Shutdown logic here
    if (AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn())
    {
        // Implement the Rain of Shutdown action
        // For example, spawn particle effects, apply damage, etc.

        Cast<ACubeBossAI>(OwnerActor)->bIsAttacking = true;

        Attack(OwnerComp);

        FTimerHandle SkillHandle;
        OwnerComp.GetWorld()->GetTimerManager().SetTimer(SkillHandle, [OwnerActor]()
        {
            if(OwnerActor->IsValidLowLevel())
            {
                Cast<ACubeBossAI>(OwnerActor)->bIsAttacking = false;
            }
        }, 15.f, false);
    }

    UE_LOG(LogTemp, Log, TEXT("Rain of Shutdown"));

    return EBTNodeResult::Succeeded;
}

void UBTTask_RainOfShutDown::Attack(UBehaviorTreeComponent& OwnerComp)
{
    ACubeBossAI* Boss = Cast<ACubeBossAI>(OwnerComp.GetAIOwner()->GetPawn());
    if (!Boss) return;

    TArray<UStaticMeshComponent*> StaticMeshes = Boss->StaticMeshComponents;
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) return;

    AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
    if (!TargetActor) return;

    // Store initial positions of static meshes
    InitialTransforms.Empty();
    for (UStaticMeshComponent* Mesh : StaticMeshes)
    {
        InitialTransforms.Add(Mesh->GetComponentTransform());

        Mesh->SetCollisionProfileName("Custom");
        Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
        Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
        Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
    }

    // Schedule the movement of each static mesh
    for (int32 i = 0; i < 7; i++)
    {
        UStaticMeshComponent* StaticMesh = StaticMeshes[i];
        FVector Location = TargetActor->GetActorLocation();
        UE_LOG(LogTemp, Log, TEXT("Target Location : %f, %f, %f"), Location.X, Location.Y, Location.Z);
        FTimerHandle TimerHandle;

        Boss->GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([StaticMesh, Location, Boss, i, this]
        {
            if(Boss->IsValidLowLevel())
            {
                FallingStaticMesh(StaticMesh, Location, Boss, i);
            }
        }), i * 1.5f, false);
    }
}

/*
void UBTTask_RainOfShutDown::ThrowStaticMesh(UStaticMeshComponent* StaticMesh, FVector TargetLocation,
    ACubeBossAI* Boss, int32 MeshIndex)
{
    if (!StaticMesh || !Boss) return;

    FVector Location = StaticMesh->GetComponentLocation();
    StaticMesh->SetWorldLocation(FVector(Location.X, Location.Y, Location.Z + 300));

    StaticMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

    FVector CurrentLocation = StaticMesh->GetComponentLocation();
    StaticMesh->SetWorldLocation(FVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + 500.f));

    FVector FinalTargetLocation = TargetLocation;

    // If not the first mesh, calculate a random location around the target
    if (MeshIndex > 0)
    {
        FVector RandomOffset = FMath::VRand() * FMath::FRandRange(0.0f, 300.0f);
        FinalTargetLocation += RandomOffset;
    }

    // Calculate the direction and force to apply
    FVector Direction = FinalTargetLocation - StaticMesh->GetComponentLocation();
    Direction.Normalize();
    float ForceMagnitude = 2000.0f; // Adjust this value based on desired throw force
    FVector Force = Direction * ForceMagnitude;

    // Enable physics simulation
    StaticMesh->SetSimulatePhysics(true);

    // Apply force to the static mesh
    StaticMesh->AddImpulse(Force, NAME_None, true);

    // Schedule the static mesh to return to its original position
    FTimerDelegate ReturnDelegate;
    ReturnDelegate.BindLambda([StaticMesh, InitialTransform = InitialTransforms[MeshIndex], Boss]
    {
        // Disable physics simulation
        StaticMesh->SetSimulatePhysics(false);
        StaticMesh->SetWorldTransform(InitialTransform, false, nullptr, ETeleportType::TeleportPhysics);
    });

    FTimerHandle ReturnHandle;
    Boss->GetWorld()->GetTimerManager().SetTimer(ReturnHandle, ReturnDelegate, 10.f - MeshIndex, false); // Adjust this delay as needed
}*/

void UBTTask_RainOfShutDown::FallingStaticMesh(UStaticMeshComponent* StaticMesh, FVector TargetLocation,
    ACubeBossAI* Boss, int32 MeshIndex)
{
    // 첫 번째 메시를 제외한 나머지 메시의 경우, 타겟 액터의 주변 3미터 반경 내에서 랜덤 위치를 생성
    if (MeshIndex > 0)
    {
        FVector2D RandomOffset = FMath::RandPointInCircle(1000.f); // 300 units is 3 meters
        TargetLocation.X += RandomOffset.X;
        TargetLocation.Y += RandomOffset.Y;
        TargetLocation.Z += 800.f;
    }

    if(Boss->IsValidLowLevel())
    {
        Boss->HideAndSpawnActor(StaticMesh, TargetLocation);
    }


    // Move the static mesh above the target location
    // FVector StartLocation = FVector(TargetLocation.X, TargetLocation.Y, TargetLocation.Z + 800.f);
    // StaticMesh->SetWorldLocation(StartLocation);


    /*// Schedule the static mesh to return to its original position
    FTimerDelegate ReturnDelegate;
    ReturnDelegate.BindLambda([StaticMesh, InitialTransform = InitialTransforms[MeshIndex]]
    {
        // Disable physics simulation
        StaticMesh->SetSimulatePhysics(false);
        StaticMesh->SetWorldTransform(InitialTransform, false, nullptr, ETeleportType::TeleportPhysics);
    });*/

    // FTimerHandle ReturnHandle;
    // Boss->GetWorld()->GetTimerManager().SetTimer(ReturnHandle, ReturnDelegate, 7.f - MeshIndex, false);

    if(MeshIndex == 5)
    {
        SetCooldown(Boss);
    }
}

void UBTTask_RainOfShutDown::SetCooldown(ACubeBossAI* Boss) const
{
    // Store the current time in the blackboard
    if(Boss->IsValidLowLevel()) return;
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Boss: %s"), *Boss->GetName());
        float CurrentTime = Boss->GetWorld()->GetTimeSeconds();
        if(Boss)
        {
            Cast<ACubeBossAIController>(Boss->GetController())->GetBlackboardComponent()->SetValueAsFloat(CooldownKey, CurrentTime);
        }
    }
}
