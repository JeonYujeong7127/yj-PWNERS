// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AINavMeshBoundsVolume.h"

#include "Virus.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "AI/AIController/AggressiveAIController.h"
#include "Components/BrushComponent.h"
#include "WorldPartition/ContentBundle/ContentBundleLog.h"

AAINavMeshBoundsVolume::AAINavMeshBoundsVolume()
{
    GetBrushComponent()->SetCollisionProfileName("OverlapAll");
    GetBrushComponent()->SetGenerateOverlapEvents(true);
}

void AAINavMeshBoundsVolume::BeginPlay()
{
    Super::BeginPlay();


    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
    {
        TArray<AActor*> OverlappingActors;
        GetOverlappingActors(OverlappingActors);

        for (AActor* OverlappingActor : OverlappingActors)
        {
            if(Cast<AVirusAIBase>(OverlappingActor))
            {
                AIs.Add(Cast<AVirusAIBase>(OverlappingActor));
            }
        }
    }), 1.f, false);

}

void AAINavMeshBoundsVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    FindPlayer();
}

void AAINavMeshBoundsVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);
    FindPlayer();
}

void AAINavMeshBoundsVolume::FindPlayer()
{
    if(HasAuthority())
    {
        for(auto AI : AIs)
        {
            if(AI == nullptr) continue;

            if(AController* Controller = AI->GetController())
            {
                if(AAggressiveAIController* AIController = Cast<AAggressiveAIController>(Controller))
                {
                    AIController->PlayersInNavMesh.Empty();
                }
            }
        }

        TArray<AActor*> OverlappingActors;
        GetOverlappingActors(OverlappingActors);

        // 플레이어가 navmesh 안에 있는지 여부
        bool bIsPlayerIn = false;

        for(auto OverlappingActor : OverlappingActors)
        {
            if(OverlappingActor == nullptr) continue;

            if(APawn* Pawn = Cast<APawn>(OverlappingActor))
            {
                if(Pawn->IsPlayerControlled())
                {
                    for(auto AI : AIs)
                    {
                        if(AI == nullptr) continue;
                        if(AAggressiveAIController* AIController = Cast<AAggressiveAIController>(AI->GetController()))
                        {
                            AIController->PlayersInNavMesh.Add(Cast<APawn>(OverlappingActor));
                        }
                    }
                }
                bIsPlayerIn = true;
            }
        }

        for(auto AI : AIs)
        {
            if(AI == nullptr) continue;
            AI->bIsPlayerIn = bIsPlayerIn;
        }
    }
}
