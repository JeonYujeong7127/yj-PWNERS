// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTService_AnyoneInAttackRange.h"

#include "AIController.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "AI/VirusAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_AnyoneInAttackRange::UBTService_AnyoneInAttackRange()
{
    Interval = 0.5f;
}

void UBTService_AnyoneInAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    //폰의 정보를 가져온다
    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
    {
        UE_LOG(LogTemp, Log,  TEXT("ConrollingPawn is Null"));
        return;
    }

    if(AVirusAIBase* VirusAI = Cast<AVirusAIBase>(ControllingPawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISPLAYERINATTACKRANGE, VirusAI->bIsPlayerInAttackRange);
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGETINATTACKRANGE, VirusAI->TargetPlayerInAttackRange);
    }
    else
    {
        UE_LOG(LogTemp, Log,  TEXT("ConrollingPawn is not AVirusAIBase"));
        return;
    }
}
