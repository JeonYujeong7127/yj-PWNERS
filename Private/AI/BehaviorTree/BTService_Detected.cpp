// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTService_Detected.h"
#include "AIController.h"
#include "AI/VirusAI.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "BehaviorTree/BlackboardComponent.h"

class AVirusAIBase;

UBTService_Detected::UBTService_Detected()
{
    NodeName = TEXT("Detect");
    Interval = 1.0f;
}

void UBTService_Detected::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    //폰의 정보를 가져온다
    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
    {
        return;
    }

    FVector Center = ControllingPawn->GetActorLocation();
    UWorld* World = ControllingPawn->GetWorld();
    if (nullptr == World)
    {
        return;
    }

    AVirusAIBase* AIPawn = Cast<AVirusAIBase>(ControllingPawn);
    if (nullptr == AIPawn)
    {
        return;
    }

    // 정찰 범위 설정 후 정찰
    float DetectRadius = AIPawn->GetAIDetectRange();

    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);

    bool bResult = World->OverlapMultiByChannel(
        OverlapResults,
        Center,
        FQuat::Identity,
        ECollisionChannel::ECC_WorldDynamic,
        FCollisionShape::MakeSphere(DetectRadius),
        CollisionQueryParam
    );

    if (bResult)
    {
        for (auto const& OverlapResult : OverlapResults)
        {
            APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
            if (Pawn && Pawn->GetController()->IsPlayerController())
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
                return;
            }
        }
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
}
