// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animation/AIAnimInstanceBase.h"

#include "AI/AICharacter/VirusAIBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAIAnimInstanceBase::UAIAnimInstanceBase()
{

}

void UAIAnimInstanceBase::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    Owner = Cast<ACharacter>(GetOwningActor());
    if(Owner) Movement = Owner->GetCharacterMovement();
}

void UAIAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if(Movement) Velocity = Movement->Velocity;
    AVirusAIBase* VirusAI = Cast<AVirusAIBase>(TryGetPawnOwner());
    if(VirusAI)
    {
        bIsAttacking = VirusAI->bIsAttacking;
    }
}
