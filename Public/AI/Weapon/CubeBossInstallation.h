// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFExplosiveObject.h"
#include "CubeBossInstallation.generated.h"

UCLASS()
class VIRUS_API ACubeBossInstallation : public AGGFExplosiveObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACubeBossInstallation();
    void SetBoss(class ACubeBossAI* CubeBoss);
    void SetInstallationNum(int8 Num);

    UPROPERTY()
    class UStaticMeshComponent* StaticMeshComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Style")
    TArray<class UStaticMesh*> StaticMeshes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Style")
    UMaterial* GlowMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void Destroyed() override;

    // Add/Remove Gameplay Tag
    void AddGameplayTag(struct FGameplayTag Tag);
    void RemoveGameplayTag(struct FGameplayTag Tag);

    UPROPERTY()
    class ACubeBossAI* Boss;

    UPROPERTY(ReplicatedUsing=OnRep_IsActivated)
    bool bIsActivated = false;

    UFUNCTION()
    void OnRep_IsActivated();

    int8 InstallationNum = 0;

    UPROPERTY(ReplicatedUsing=OnRep_StaticMeshNum)
    int8 StaticMeshNum = 0;

    UFUNCTION()
    void OnRep_StaticMeshNum();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void SetActivated(bool Value);
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(ReplicatedUsing=OnRep_ReplcatedLocation)
    FVector ReplicatedLocation;

    UPROPERTY(ReplicatedUsing=OnRep_ReplicatedRotation)
    FRotator ReplicatedRotation;

    UFUNCTION()
    void OnRep_ReplcatedLocation();

    UFUNCTION()
    void OnRep_ReplicatedRotation();
};
