// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIController/CubeBossAIController.h"

#include "AI/AICharacter/CubeBossAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACubeBossAIController::ACubeBossAIController()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Virus/Actors/AI/CubeBossAI/BB_CubeBossAI.BB_CubeBossAI"));
    if (BBObject.Succeeded())
    {
        BBAsset = BBObject.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Virus/Actors/AI/CubeBossAI/BT_CubeBossAI.BT_CubeBossAI"));
    if (BTObject.Succeeded())
    {
        BTAsset = BTObject.Object;
    }

    // AI Perception 설정
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
    AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");
    AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
    AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
    AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
    AISenseConfigSight->SightRadius = 1000.f;
    AISenseConfigSight->LoseSightRadius = 1500.f;
    AISenseConfigSight->PeripheralVisionAngleDegrees = 30.f;

    AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
    AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
}

void ACubeBossAIController::SetIsAttacking(bool Value)
{
    Cast<ACubeBossAI>(GetPawn())->bIsAttacking = Value;
    GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttacking"), Value);
}

void ACubeBossAIController::BeginPlay()
{
    Super::BeginPlay();

    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void ACubeBossAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void ACubeBossAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
}

void ACubeBossAIController::RunAI()
{
    UBlackboardComponent* BlackboardPtr = Blackboard.Get();
    if (UseBlackboard(BBAsset, BlackboardPtr))
    {
        bool RunResult = RunBehaviorTree(BTAsset);
        ensure(RunResult);
    }

    GetBlackboardComponent()->SetValueAsBool(TEXT("IsInSecondPhase"), true);
}

void ACubeBossAIController::StopAI()
{
    if (UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent)) {
        BTComponent->StopTree(EBTStopMode::Safe);
    }
}
