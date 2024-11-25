// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/GGFMenuWidget.h"
#include "SelectSkillWidget.generated.h"

class UGGFSkillDefinition;
class UButton;
class UImage;
class USkillPopUpWidget;

// TODO 리팩토링
/**
 * 로비에서 사용하기 위한 스킬 선택 메뉴 위젯
 */
UCLASS()
class VIRUS_API USelectSkillWidget : public UGGFMenuWidget
{
	GENERATED_BODY()

protected:
    /* 컴포넌트 */

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> QMovingTriangle;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> EMovingTriangle;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Img_QTriangle;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Img_ETriangle;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Img_FirstSkill;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Img_SecondSkill;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_QSkill;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_ESkill;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_Select;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillPower;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillBondage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillDark;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillAggro;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillShield;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillSleeping;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillSpupping;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillBang;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillLighting;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillTurret;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillFloorHeal;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillHeal;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillPurification;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillSacrifice;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_SkillSalvation;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_ResetSkill;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> BT_ESC;

    /* 멤버 변수 */

    // 스킬 팝업 위젯 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> PopUpWidgetClass;

    // 스킬 팝업 위젯 인스턴스
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<int32, TObjectPtr<USkillPopUpWidget>> PopUpWidgets;

    // 버튼 별로 매핑된 스킬 ID
    TMap<int32, TObjectPtr<UButton>> ButtonSkillIDMap;

    // TODO 리팩토링
    // 버튼 별로 매핑된 스킬 이름
    TMap<TObjectPtr<UButton>, FName> ButtonSkillNameMap;

    // 현재 선택된 Q 스킬
    int32 PrimarySkillID = 0;

    // 현재 선택된 E 스킬
    int32 SecondarySkillID = 1;

    // 스킬 트리에서 선택된 Q 스킬 슬롯
    UPROPERTY()
    TObjectPtr<UButton> SelectedPrimarySkillButton;

    // 스킬 트리에서 선택된 E 스킬 슬롯
    UPROPERTY()
    TObjectPtr<UButton> SelectedSecondarySkillButton;

    // 선택된 스킬 슬롯에서 선택된 Q 혹은 E 스킬 슬롯
    UPROPERTY()
    TObjectPtr<UButton> SelectedSkillButton;

    bool bIsHovered = false;

    // 스킬 데이터 에셋 ID 맵
    UPROPERTY()
    TMap<int32, TObjectPtr<UGGFSkillDefinition>> SkillDefinitionIDMap;

protected:
    /* UserWidget */

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION()
    void OnClicked_BTSkill();

    UFUNCTION()
    void OnClicked_BTSelect();

    UFUNCTION()
    void OnClicked_BTQSkill();

    UFUNCTION()
    void OnClicked_BTESkill();

    UFUNCTION()
    void OnClicked_BTResetSkill();

    UFUNCTION()
    void OnHovered_BTSkill();

    UFUNCTION()
    void OnUnHovered_BTSkill();

    UFUNCTION()
    void OnClicked_BTEsc();

    void SetImageFromFile(UImage* ImageWidget, const FString& SkillName);

    void SetSelected(UButton* SelectedButton);
    void SetNoSelected(UButton* SelectedButton);

    void PlayTriangleAnimation(const FString& Triangle, bool bIsPlay);
};
