// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Components/WidgetComponent.h"
#include "Characters/GGFThirdPersonCharacter_Retarget.h"
#include "VirusPlayerCharacter.generated.h"

/**
 * Virus 프로젝트 전용 플레이어 캐릭터
 */
UCLASS()
class AVirusPlayerCharacter : public AGGFThirdPersonCharacter_Retarget
{
	GENERATED_BODY()

    /* 컴포넌트 */

    // 플레이어 이름 표시를 위한 위젯 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetPlayerNameWidgetComponent, Category = "Component")
    TObjectPtr<UWidgetComponent> PlayerNameWidgetComponent;

    // TODO GGF 플러그인으로 이전 예정
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetFirstPersonCamera, Category = "Component")
    TObjectPtr<UCameraComponent> FirstPersonCamera;

public:
    AVirusPlayerCharacter();

    /* Actor */

    virtual void PostInitializeComponents() override;

    /* Pawn */

    virtual void NotifyControllerChanged() override;
    virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;

    virtual void OnDead_Implementation() override;

protected:
    UFUNCTION(BlueprintCallable)
    virtual void UpdatePlayerName(APlayerState* NewPlayerState);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UWidgetComponent* GetPlayerNameWidgetComponent() const { return PlayerNameWidgetComponent; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; }
};
