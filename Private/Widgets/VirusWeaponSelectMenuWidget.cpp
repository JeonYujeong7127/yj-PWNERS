// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/VirusWeaponSelectMenuWidget.h"

#include "Components/Button.h"
#include "Players/VirusPlayerState.h"
#include "Widgets/VirusWeaponSlotWidget.h"

void UVirusWeaponSelectMenuWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    WeaponSlots.Add(WeaponSlot_0);
    WeaponSlots.Add(WeaponSlot_1);
    WeaponSlots.Add(WeaponSlot_2);
    WeaponSlots.Add(WeaponSlot_3);

    WeaponIDMap.Emplace(WeaponSlot_0->SelectButton, 0);
    WeaponIDMap.Emplace(WeaponSlot_1->SelectButton, 1);
    WeaponIDMap.Emplace(WeaponSlot_2->SelectButton, 2);
    WeaponIDMap.Emplace(WeaponSlot_3->SelectButton, 3);

    /* 이벤트 바인딩 */

    SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnSelectButtonClicked);
    CustomButton->OnClicked.AddDynamic(this, &ThisClass::OnCustomButtonClicked);
    EscapeButton->OnClicked.AddDynamic(this, &ThisClass::OnEscapeButtonClicked);

    WeaponSlot_0->SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnWeaponSlotButtonClicked);
    WeaponSlot_1->SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnWeaponSlotButtonClicked);
    WeaponSlot_2->SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnWeaponSlotButtonClicked);
    WeaponSlot_3->SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnWeaponSlotButtonClicked);
}

void UVirusWeaponSelectMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 슬롯 초기화
    WeaponSlot_0->SetWeaponID(0);
    WeaponSlot_1->SetWeaponID(1);
    WeaponSlot_2->SetWeaponID(2);
    WeaponSlot_3->SetWeaponID(3);
    /* 데이터 읽어오기 */
}

void UVirusWeaponSelectMenuWidget::OnEscapeButtonClicked()
{
    // TODO 뒤로 가기로 대체

    RemoveFromParent();
}

void UVirusWeaponSelectMenuWidget::OnSelectButtonClicked()
{
    if(SelectedWeaponButton)
    {
        if(auto VirusPlayerState = Cast<AVirusPlayerState>(GetOwningPlayerState()))
        {
            VirusPlayerState->SetWeaponID(WeaponIDMap[SelectedWeaponButton]);
        }
    }

    // TODO 선택 버튼 비활성화 등의 효과로 대체

    RemoveFromParent();
    Destruct();
}

void UVirusWeaponSelectMenuWidget::OnCustomButtonClicked()
{
    // TODO
}

void UVirusWeaponSelectMenuWidget::OnWeaponSlotButtonClicked()
{
    for(auto WeaponSlot : WeaponSlots)
    {
        if(WeaponSlot->SelectButton->IsHovered())
        {
            if(SelectButton != WeaponSlot->SelectButton)
            {
                SelectedWeaponButton = WeaponSlot->SelectButton;
                SetSelected(WeaponSlot->SelectButton);
            }
        }
        else
        {
            SetUnSelected(WeaponSlot->SelectButton);
        }
    }

    /*
    if(WeaponSlot_0->SelectButton->IsHovered())
    {
        if(SelectedWeaponButton != WeaponSlot_0->SelectButton)
        {
            SelectedWeaponButton = WeaponSlot_0->SelectButton;
        }
    }
    else if(WeaponSlot_1->SelectButton->IsHovered())
    {
        if(SelectedWeaponButton != WeaponSlot_1->SelectButton)
        {
            SelectedWeaponButton = WeaponSlot_1->SelectButton;
        }
    }
    else if(WeaponSlot_2->SelectButton->IsHovered())
    {
        if(SelectedWeaponButton != WeaponSlot_2->SelectButton)
        {
            SelectedWeaponButton = WeaponSlot_2->SelectButton;
        }
    }
    else if(WeaponSlot_3->SelectButton->IsHovered())
    {
        if(SelectedWeaponButton != WeaponSlot_3->SelectButton)
        {
            SelectedWeaponButton = WeaponSlot_3->SelectButton;
        }
    }
    */
}

void UVirusWeaponSelectMenuWidget::SetSelected(TObjectPtr<UButton> Button)
{
    FButtonStyle ButtonStyle = Button->GetStyle();

    FString FilePath = "/Game/Arts/UI/weapon/weaponslot3.weaponslot3";
    if (UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *FilePath)))
    {
        // Create a new slate brush for the normal image
        FSlateBrush NormalBrush = ButtonStyle.Normal;
        NormalBrush.SetResourceObject(Texture);

        // Set the normal image brush
        ButtonStyle.SetNormal(NormalBrush);

        // Apply the updated style to the button
        Button->SetStyle(ButtonStyle);
    }
}

void UVirusWeaponSelectMenuWidget::SetUnSelected(TObjectPtr<UButton> Button)
{
    FButtonStyle ButtonStyle = Button->GetStyle();

    FString FilePath = "/Game/Arts/UI/weapon/weaponslot.weaponslot";
    if (UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *FilePath)))
    {
        // Create a new slate brush for the normal image
        FSlateBrush NormalBrush = ButtonStyle.Normal;
        NormalBrush.SetResourceObject(Texture);

        // Set the normal image brush
        ButtonStyle.SetNormal(NormalBrush);

        // Apply the updated style to the button
        Button->SetStyle(ButtonStyle);
    }
}
