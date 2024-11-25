// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AICharacter/AggressiveAI.h"
#include "SpiderAI.generated.h"

class USoundCue;

/**
 *
 */
UCLASS()
class VIRUS_API ASpiderAI : public AAggressiveAI
{
	GENERATED_BODY()

public:
    ASpiderAI();
    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void Bomb();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USoundCue> BombSoundCue;

    UPROPERTY()
    const USkeletalMeshSocket* WeaponSocket;

    UPROPERTY(ReplicatedUsing=OnRep_IsBomb, BlueprintReadOnly)
    bool bIsBomb = false;

    UFUNCTION()
    void OnRep_IsBomb();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
