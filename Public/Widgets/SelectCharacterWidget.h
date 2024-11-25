// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/GGFMenuWidget.h"
#include "SelectCharacterWidget.generated.h"

class UButton;

// TODO 하드 코딩 대신 데이터 서브 시스템 연동
// TODO 캐릭터 슬롯 위젯은 별도의 클래스로 분리
/**
 * 로비에서 사용하기 위한 캐릭터 선택 메뉴 위젯
 */
UCLASS()
class VIRUS_API USelectCharacterWidget : public UGGFMenuWidget
{
	GENERATED_BODY()

public:
    /* 컴포넌트 */

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SASER;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_MELISSA;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_LEN;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_BAY;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_Select;

    // 버튼 별로 설정된 캐릭터 ID
    TMap<TObjectPtr<UButton>, int32> ButtonCharacterMap;

    // 현재 활성화된 버튼
    UPROPERTY()
    TObjectPtr<UButton> CurrentSelectButton;

    // 현재 선택된 캐릭터 이름
    int32 CurrentSelectCharacterNum;

protected:

    // 선택된 캐릭터 ID
    int32 CharacterID = 0;

    // 선택된 캐릭터 스킨 ID
    int32 CharacterSkinID = -1;

protected:
    /* UserWidget */

    virtual void NativeConstruct() override;

    /* 이벤트 */

    UFUNCTION()
    void OnClicked_BTCharacter();

    UFUNCTION()
    void OnClicked_BTSelect();

    /* 메서드 */

    // 선택한 캐릭터 버튼 활성화
    void SetSelected(UButton* SelectedButton);

    // 이전 선택한 캐릭터 버튼 비활성화
    void SetNoSelected(UButton* NotSelectedButton);

    // 캐릭터 ID 적용
    UFUNCTION(BlueprintCallable)
    virtual void ApplyCharacterID();
};
