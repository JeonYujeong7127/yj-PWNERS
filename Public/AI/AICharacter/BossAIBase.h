// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GGFCharacter.h"
#include "BossAIBase.generated.h"

UENUM(BlueprintType)
enum ESkillConditionType : int
{
    // 디폴트 (None)
    SkillConditionDefault         UMETA(DisplayName="None"),

    // 쿨타임 조건
    CoolDown		UMETA(DisplayName="Cool Down"),

    // HP 조건(eg. 30% 이하 발동)
    HPCondition	    UMETA(DisplayName="HP Condition")
};

UCLASS()
class VIRUS_API ABossAIBase : public AGGFCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossAIBase();

    float Health = 0;
    float MaxHealth = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
    UFUNCTION(BlueprintCallable)
    virtual void Die();
};
