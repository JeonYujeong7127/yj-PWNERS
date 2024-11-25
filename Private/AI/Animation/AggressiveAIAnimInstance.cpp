// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animation/AggressiveAIAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAggressiveAIAnimInstance::UAggressiveAIAnimInstance()
{

}

void UAggressiveAIAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    Owner = Cast<ACharacter>(GetOwningActor());
    if(Owner) Movement = Owner->GetCharacterMovement();
}

void UAggressiveAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if(Movement) Velocity = Movement->Velocity;
}
