// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AI/AICharacter/BossAIBase.h"
#include "CubeBossAI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackingStateChanged, bool, bIsAttacking);

/**
 *
 */
UCLASS()
class VIRUS_API ACubeBossAI : public ABossAIBase
{
	GENERATED_BODY()

public:
    ACubeBossAI();

    void SetAIActivated(bool Value) const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UClass* CubeBossController;

    bool bIsDamageable = false;

    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UGGFGE_Heal> HealAbilityClass;

    void CoreBoom();

    void Heal();

    bool bIsHeal = false;

    void SetInvinsible(bool Value);
    void SetDamageable(bool Value);

    void AddInstallation(class ACubeBossInstallation* Installation);
    void ActivateNextInstallation();
    void InstallationDestroyed(ACubeBossInstallation* DestroyedInstallation);

    void PhantomRecoveryInstall();

    // SpinOfDestruction 공격 함수
    void SpinOfDestructionFire();

    // 스태틱 메시 모두 루트에 붙이는 함수
    void SetStaticMeshToRoot();

    // 원래 스태틱 메시 컴포넌트를 숨기고 다시 보이게 설정하는 함수
    void HideAndSpawnActor(class UStaticMeshComponent* StaticMesh, const FVector& TargetLocation);

    // 스태틱 메시를 다시 보이게 설정하는 함수
    void ShowOriginalStaticMesh(class UStaticMeshComponent* StaticMesh);

    bool bIsSpinning = false;
    bool bIsRising = false;

    // 새롭게 스폰된 액터의 참조를 저장하기 위한 변수
    UPROPERTY()
    AActor* SpawnedActor;

    UPROPERTY()
    TArray<AActor*> SpawnedActors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TSubclassOf<AActor> InstallationClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TSubclassOf<AActor> BlockClass;

    UPROPERTY(ReplicatedUsing=OnRep_IsAttacking)
    bool bIsAttacking;

    // Array to hold multiple StaticMeshComponents
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TArray<UStaticMeshComponent*> StaticMeshComponents;

private:
    void StartRising();
    void StartFalling();
    void DealDamage();

    virtual void OnDead_Implementation() override;

    FGameplayAttribute Attribute;

    FVector InitLocation;

    FVector StartLocation;
    FVector TargetLocation;
    float RiseDuration = 3.f;
    float FallDuration = 0.5f;
    float CurrentTime;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;
    virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAttackingStateChanged OnAttackingStateChanged;

    // 델리게이트에 바인딩된 함수
    UFUNCTION()
    void HandleAttackingStateChanged(bool bNewIsAttacking);

    UFUNCTION()
    void OnRep_IsAttacking();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Counter for the number of times SpinOfDestructionFire has been called
    int32 FireCount;

    // Timer handle for managing SpinOfDestructionFire
    FTimerHandle FireHandle;

    UPROPERTY()
    TArray<ACubeBossInstallation*> Installations;

    int32 CurrentInstallationIndex;
};
