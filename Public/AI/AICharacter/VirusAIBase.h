// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GGFCharacter.h"
#include "VirusAIBase.generated.h"

UENUM(BlueprintType)
enum class EAttackType : uint8
{
    // 디폴트 (None)
    AttackTypeDefault        UMETA(DisplayName="None"),

    // 원거리 단일 총알
    FarBullet                UMETA(DisplayName="Bullet"),

    // 원거리 복수 포탄 발사 (타깃 향해 발사 후 폭발 범위에 닿은 적 모두 타격)
    FarBomb                  UMETA(DisplayName="Bomb"),

    // 근접 단일 팔 공격
    CloseArmAttack           UMETA(DisplayName="ArmAttack"),

    // 근접 복수 휠윈드 (팔 범위에 닿은 적 모두 타격)
    CloseWheelWind           UMETA(DisplayName="Wheel Wind"),

    // 자폭
    CloseSuicide             UMETA(DisplayName="Suicide"),
};

UCLASS()
class VIRUS_API AVirusAIBase : public AGGFCharacter
{
	GENERATED_BODY()

public:
    AVirusAIBase();
    virtual void BeginPlay() override;

    bool CanAttack(AActor* PlayerActor);

    UFUNCTION()
    void PlayAttackSound();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UCapsuleComponent* AttackRangeCapsuleComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UCapsuleComponent* AttackCapsuleComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect")
    class UParticleSystem* ParticleSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
    class UAnimMontage* DieMongtage;

    UPROPERTY()
    class UAIAnimInstanceBase* AnimInstance;

    // 현재 설정된 타깃
    UPROPERTY()
    APawn* TargetPlayer;

    // 현재 공격 범위에 있는 타깃
    UPROPERTY()
    APawn* TargetPlayerInAttackRange;

    // 공격 타입
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Combat)
    EAttackType AttackType;

    // 총알
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Combat)
    UClass* ProjectileClass;

    // 폭탄
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Combat)
    UClass* BombClass;

    float GetAIPatrolRadius() const { return AIPatrolRadius; };
    float GetAIDetectRange() const { return AIDetectRange; };
    float GetAttackRange() const { return AttackRange; };
    float GetSkillRange() const { return SkillRange; };
    float GetCoolDownTime() const { return CoolDownTime; };
    float GetHPConditionPercent() const { return HPConditionPercent; };
    float GetAttackTime() const { return AttackTime; };

    UFUNCTION()
    virtual void OnOverlapBeginInAttackCapsule(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnOverlapEndInAttackCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    virtual void OnOverlapBeginInAttackCollisionCapsule(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // 패트롤에 플레이어가 있는지
    bool bIsPlayerIn = false;

    // 공격 범위 안에 플레이어 여부
    bool bIsPlayerInAttackRange = false;

    UFUNCTION()
    void OnRep_IsAttacking();

    // 공격 중인지 여부
    UPROPERTY(ReplicatedUsing=OnRep_IsAttacking, BlueprintReadOnly, Category = "Animation")
    bool bIsAttacking = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
    class USoundCue* AttackSound;


protected:

    virtual void OnDead_Implementation() override;

    UPROPERTY()
    class UAudioComponent* AudioComponent;

    UPROPERTY()
    USkeletalMeshSocket const* AttackSocket;

    // 이동 범위
    float AIPatrolRadius = 0;

    // 플레이어 감지 범위
    float AIDetectRange = 0;

    // movementmode 설정
    EMovementMode MovementMode = MOVE_None;

    // 일반 공격 범위
    float AttackRange = 0;

    // 스킬 공격 범위
    float SkillRange = 0;

    // 쿨타임
    float CoolDownTime = 0;

    // HP 조건
    float HPConditionPercent = 0;

    // 공격 시간
    float AttackTime = 0;

    // 최대 걷기 속도
    float WalkSpeed = 0;

    // 1회 공격력
    float AttackRate = 0;

public:
    virtual void BulletAttack(APawn* TargetPawn);
    virtual void BombAttack(APawn* TargetPawn);
    virtual void ArmAttack(APawn* TargetPawn);
    virtual void WheelWindAttack(TArray<AActor*> Targets);
    virtual void SuicideAttack(APawn* TargetPawn);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
