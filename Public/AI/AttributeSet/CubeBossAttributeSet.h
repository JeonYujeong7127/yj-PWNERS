// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Attributes/GGFAttributesBase.h"
#include "CubeBossAttributeSet.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API UCubeBossAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
    UCubeBossAttributeSet();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UCubeBossAttributeSet, Health)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UCubeBossAttributeSet, MaxHealth)
};
