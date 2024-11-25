// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTService_IsLocatedHome.h"
#include "AI/VirusAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsLocatedHome::UBTService_IsLocatedHome()
{
    // NodeName = TEXT("LocatedHome");
    Interval = 1.0f;
}

void UBTService_IsLocatedHome::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    FVector HomePos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);
    FVector ActorPos = OwnerComp.GetOwner()->GetActorLocation();

    if(OwnerComp.GetOwner()->GetActorLocation() == HomePos)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISHOME, true);
    }
}
