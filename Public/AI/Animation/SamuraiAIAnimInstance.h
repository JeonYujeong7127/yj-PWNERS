// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIAnimInstanceBase.h"
#include "SamuraiAIAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API USamuraiAIAnimInstance : public UAIAnimInstanceBase
{
	GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
