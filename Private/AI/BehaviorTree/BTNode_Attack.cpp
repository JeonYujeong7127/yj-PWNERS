// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/BTNode_Attack.h"
#include "AIController.h"
#include "AI/VirusAI.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "AI/AIController/AggressiveAIController.h"
#include "AI/Animation/AIAnimInstanceBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

class AVirusAIBase;

EBTNodeResult::Type UBTNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
    
    if(AVirusAIBase* AI = Cast<AVirusAIBase>(OwnerComp.GetAIOwner()->GetCharacter()))
    {
        if(AI->bIsAttacking) return EBTNodeResult::Failed;

        AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGETINATTACKRANGE));

        if(Target)
        {
            if(!AI->CanAttack(Target)) return EBTNodeResult::Failed;
            if(!AI->bIsAttacking)
            {
                FRotator Rotation = FRotationMatrix::MakeFromX(Target->GetActorLocation() - AI->GetActorLocation()).Rotator();
                AI->SetActorRotation(Rotation);
            }

            AI->AnimInstance->bIsAttacking = true;
            AI->bIsAttacking = true;

            OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISATTACKING, true);

            if(AI->AttackSound)
            {
                AI->PlayAttackSound();
            }

            switch(AI->AttackType)
            {
                case(EAttackType::AttackTypeDefault):
                    break;

                case(EAttackType::FarBullet):
                    AI->BulletAttack(Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGETINATTACKRANGE)));
                    break;

                case(EAttackType::FarBomb):
                    AI->BombAttack(Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGETINATTACKRANGE)));
                    break;

                case(EAttackType::CloseArmAttack):
                    AI->ArmAttack(Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGETINATTACKRANGE)));
                    break;

                case(EAttackType::CloseSuicide):
                    AI->SuicideAttack(Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGETINATTACKRANGE)));
                    return EBTNodeResult::Succeeded;

                case(EAttackType::CloseWheelWind):
                    TArray<AActor*> Targets;
                    AI->AttackRangeCapsuleComponent->GetOverlappingActors(Targets);
                    AI->WheelWindAttack(Targets);
                    break;
            }

            FTimerHandle Handle;
            GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([AI]
            {
                AI->bIsAttacking = false;
                AI->AnimInstance->bIsAttacking = false;
                Cast<AAggressiveAIController>(AI->GetController())->SetIsAttacking(false);
            }), AI->GetAttackTime(), false);

            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}
