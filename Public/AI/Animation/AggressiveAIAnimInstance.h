// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AggressiveAIAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UAggressiveAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UAggressiveAIAnimInstance();

    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
    TObjectPtr<ACharacter> Owner;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
    TObjectPtr<class UCharacterMovementComponent> Movement;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
    FVector Velocity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
    bool bIsAttacking = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
    bool bIsWalking = false;
};
