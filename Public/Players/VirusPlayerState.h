// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFPlayerState.h"
#include "VirusPlayerState.generated.h"

/**
 * Virus 프로젝트 전용 기본 플레이어 스테이트 클래스
 *
 * 데이터 관리만 진행하며 데이터 사용은 필요한 클래스에서 구현하는 방식으로 설계합니다.
 */
UCLASS()
class VIRUS_API AVirusPlayerState : public AGGFPlayerState
{
	GENERATED_BODY()

protected:
    // 선택 캐릭터
    UPROPERTY(EditAnywhere, BlueprintGetter = GetCharacterID, BlueprintSetter = SetCharacterID, Category = "Config", ReplicatedUsing = OnRep_CharacterID)
    int32 CharacterID = 0;

    // 선택 캐릭터 스킨
    UPROPERTY(EditAnywhere, BlueprintGetter = GetCharacterSkinID, BlueprintSetter = SetCharacterSkinID, Category = "Config", ReplicatedUsing = OnRep_CharacterSkinID)
    int32 CharacterSkinID = -1;

    // 선택 무기
    UPROPERTY(EditAnywhere, BlueprintGetter = GetWeaponID, BlueprintSetter = SetWeaponID, Category = "Config", ReplicatedUsing = OnRep_WeaponID)
    int32 WeaponID = 0;

    // 선택 무기 스킨
    UPROPERTY(EditAnywhere, BlueprintGetter = GetWeaponSkinID, BlueprintSetter = SetWeaponSkinID, Category = "Config", ReplicatedUsing = OnRep_WeaponSkinID)
    int32 WeaponSkinID = -1;

    // 선택 Q 스킬
    UPROPERTY(EditAnywhere, BlueprintGetter = GetPrimarySkillID, BlueprintSetter = SetPrimarySkillID, Category = "Config", ReplicatedUsing = OnRep_PrimarySkillID)
    int32 PrimarySkillID = 0;

    // 선택 E 스킬
    UPROPERTY(EditAnywhere, BlueprintGetter = GetSecondarySkillID, BlueprintSetter = SetSecondarySkillID, Category = "Config", ReplicatedUsing = OnRep_SecondarySkillID)
    int32 SecondarySkillID = 1;

public:
    /* Actor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetCharacterID() const { return CharacterID; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetCharacterSkinID() const { return CharacterSkinID; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetWeaponID() const { return WeaponID; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetWeaponSkinID() const { return WeaponSkinID; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetPrimarySkillID() const { return PrimarySkillID; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetSecondarySkillID() const { return SecondarySkillID; }

    /* Setter */

    UFUNCTION(BlueprintSetter)
    virtual void SetCharacterID(int32 NewCharacterID);

    UFUNCTION(BlueprintSetter)
    virtual void SetCharacterSkinID(int32 NewCharacterSkinID);

    UFUNCTION(BlueprintSetter)
    virtual void SetWeaponID(int32 NewWeaponID);

    UFUNCTION(BlueprintSetter)
    virtual void SetWeaponSkinID(int32 NewWeaponSkinID);

    UFUNCTION(BlueprintSetter)
    virtual void SetPrimarySkillID(int32 NewPrimarySkillID);

    UFUNCTION(BlueprintSetter)
    virtual void SetSecondarySkillID(int32 NewSecondarySkillID);

protected:
    /* PlayerState */

    // SeamlessTravel이 활성화된 경우에만 호출됩니다.
    virtual void CopyProperties(APlayerState* PlayerState) override;

    /* RPC */

    UFUNCTION(Server, Reliable)
    void ServerSetCharacterID(int32 NewCharacterID);

    UFUNCTION(Server, Reliable)
    void ServerSetCharacterSkinID(int32 NewCharacterSkinID);

    UFUNCTION(Server, Reliable)
    void ServerSetWeaponID(int32 NewWeaponID);

    UFUNCTION(Server, Reliable)
    void ServerSetWeaponSkinID(int32 NewWeaponSkinID);

    UFUNCTION(Server, Reliable)
    void ServerSetPrimarySkillID(int32 NewPrimarySkillID);

    UFUNCTION(Server, Reliable)
    void ServerSetSecondarySkillID(int32 NewSecondarySkillID);

    /* 리플리케이트 */

    UFUNCTION()
    virtual void OnRep_CharacterID(int32 OldCharacterID);

    UFUNCTION()
    virtual void OnRep_CharacterSkinID(int32 OldCharacterSkinID);

    UFUNCTION()
    virtual void OnRep_WeaponID(int32 OldWeaponID);

    UFUNCTION()
    virtual void OnRep_WeaponSkinID(int32 OldWeaponSkinID);

    UFUNCTION()
    virtual void OnRep_PrimarySkillID(int32 OldPrimarySkillID);

    UFUNCTION()
    virtual void OnRep_SecondarySkillID(int32 OldSecondarySkillID);
};
