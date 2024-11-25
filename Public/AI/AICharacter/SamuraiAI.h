// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AICharacter/VirusAIBase.h"
#include "SamuraiAI.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API ASamuraiAI : public AVirusAIBase
{
	GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetWeaponMesh, Category = "Component")
    TObjectPtr<USkeletalMeshComponent> WeaponMesh;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName WeaponSocketName = "weapon_r";

public:
    ASamuraiAI();

    /* Actor */

    virtual void BeginPlay() override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
};
