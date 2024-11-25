// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIController/NonAggressiveAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "AI/VirusAI.h"
#include "Characters/VirusPlayerCharacter.h"
#include "Perception/AISenseConfig_Damage.h"

ANonAggressiveAIController::ANonAggressiveAIController()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Virus/Actors/AI/NonAggressiveAI/BB_NonAggressiveAI.BB_NonAggressiveAI"));
    if (BBObject.Succeeded())
    {
        BBAsset = BBObject.Object;
    }
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Virus/Actors/AI/NonAggressiveAI/BT_NonAggressiveAI.BT_NonAggressiveAI"));
    if (BTObject.Succeeded())
    {
        BTAsset = BTObject.Object;
    }

    SetPerceptionConfig();
    // Add an team id. I use e.g enums for the affiliation types
    // 0: 플레이어 / 1: 적 AI
    AAIController::SetGenericTeamId(FGenericTeamId(1));
}

void ANonAggressiveAIController::BeginPlay()
{
    Super::BeginPlay();

    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void ANonAggressiveAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    RunAI();
}

void ANonAggressiveAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if(Cast<AVirusPlayerCharacter>(Actor))
    {
        Blackboard.Get()->SetValueAsObject(BBKEY_TARGET, Actor);
    }
}

ETeamAttitude::Type ANonAggressiveAIController::GetTeamAttitudeTowards(const AActor& Other) const
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

void ANonAggressiveAIController::RunAI()
{
    UBlackboardComponent* BlackboardPtr = Blackboard.Get();
    if (UseBlackboard(BBAsset, BlackboardPtr))
    {
        Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

        bool RunResult = RunBehaviorTree(BTAsset);
        ensure(RunResult);
    }
}

void ANonAggressiveAIController::StopAI()
{
    UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (BTComponent) {
        BTComponent->StopTree(EBTStopMode::Safe);
    }
}

void ANonAggressiveAIController::SetPerceptionConfig()
{
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
    AISenseConfigDamage = CreateDefaultSubobject<UAISenseConfig_Damage>("SenseDamage");

    AIPerceptionComponent->ConfigureSense(*AISenseConfigDamage);
    AIPerceptionComponent->SetDominantSense(UAISenseConfig_Damage::StaticClass());
}
