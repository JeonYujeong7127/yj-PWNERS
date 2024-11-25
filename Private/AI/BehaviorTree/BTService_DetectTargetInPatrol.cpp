// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTService_DetectTargetInPatrol.h"

#include "AIController.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "AI/AIController/AggressiveAIController.h"
#include "BehaviorTree/BlackboardData.h"

void UBTService_DetectTargetInPatrol::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}
