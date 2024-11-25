// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIController/AggressiveAIController.h"

#include "Virus.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "AI/VirusAI.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "Characters/VirusPlayerCharacter.h"

AAggressiveAIController::AAggressiveAIController()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Virus/Actors/AI/AggresiveAI/BB_AggressiveAI.BB_AggressiveAI"));
    if (BBObject.Succeeded())
    {
        BBAsset = BBObject.Object;
    }
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Virus/Actors/AI/AggresiveAI/BT_AggressiveAITest.BT_AggressiveAITest"));
    if (BTObject.Succeeded())
    {
        BTAsset = BTObject.Object;
    }

    // AI Perception 설정

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);

    AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");

    AISenseConfigSight->SightRadius = 1000.0f; // Set the sight radius
    AISenseConfigSight->LoseSightRadius = 1200.0f; // Set the lose sight radius
    AISenseConfigSight->PeripheralVisionAngleDegrees = 90.0f; // Set the field of view angle
    AISenseConfigSight->SetMaxAge(5.0f); // Set the maximum age of sensed stimuli
    AISenseConfigSight->AutoSuccessRangeFromLastSeenLocation = -1.0f; // No auto success range
    AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
    AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
    AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;

    AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
    AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
}

void AAggressiveAIController::BeginPlay()
{
    Super::BeginPlay();
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void AAggressiveAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    RunAI();
}

void AAggressiveAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if(Cast<AVirusPlayerCharacter>(Actor))
    {
        if(Blackboard.Get()->GetValueAsObject(BBKEY_TARGET) == nullptr)
        {
            Blackboard.Get()->SetValueAsObject(BBKEY_TARGET, Actor);
            Cast<AVirusAIBase>(GetPawn())->TargetPlayer = Cast<APawn>(Actor);
        }
    }
}

void AAggressiveAIController::SetbIsPlayerInPatrol(bool bIsPlayerInPatrol)
{

}

ETeamAttitude::Type AAggressiveAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    if (APawn const* OtherPawn = Cast<APawn>(&Other))
    {
        if (auto const TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
        {
            if (TeamAgent->GetGenericTeamId() == FGenericTeamId(1))
            {
                return ETeamAttitude::Friendly;
            }
            else
            {
                return ETeamAttitude::Hostile;
            }
        }
    }
    return ETeamAttitude::Neutral;
}

void AAggressiveAIController::SetTargetInAttackRange(APawn* Target)
{
    Blackboard->SetValueAsObject(BBKEY_TARGETINATTACKRANGE, Target);
    Blackboard->SetValueAsObject(BBKEY_TARGET, Target);
}

void AAggressiveAIController::SetIsAttacking(bool Value)
{
    Blackboard->SetValueAsBool(BBKEY_ISATTACKING, false);
}

void AAggressiveAIController::RunAI()
{
    UBlackboardComponent* BlackboardPtr = Blackboard.Get();
    if (UseBlackboard(BBAsset, BlackboardPtr))
    {
        Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

        bool RunResult = RunBehaviorTree(BTAsset);
        ensure(RunResult);
    }
}

void AAggressiveAIController::StopAI()
{
    UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (BTComponent) {
        BTComponent->StopTree(EBTStopMode::Safe);
    }
}
