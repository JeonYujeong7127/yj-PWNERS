// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ClosetWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UClosetWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Get reference to the player controller
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
    {
        PlayerController->SetShowMouseCursor(true);
        PlayerController->SetInputMode(FInputModeUIOnly());
    }

    BT_Weapon->OnClicked.Clear();
    BT_Skill->OnClicked.Clear();
    BT_ESC->OnClicked.Clear();

    BT_Weapon->OnClicked.AddDynamic(this, &UClosetWidget::OnClicked_BTWeapon);
    BT_Skill->OnClicked.AddDynamic(this, &UClosetWidget::OnClicked_BTSkill);
    BT_ESC->OnClicked.AddDynamic(this, &UClosetWidget::OnClicked_BTESC);
}

void UClosetWidget::OnClicked_BTESC()
{
    // Get reference to the player controller
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
    {
        PlayerController->SetShowMouseCursor(false);
        PlayerController->SetInputMode(FInputModeGameOnly());
    }

    RemoveFromParent();
}

void UClosetWidget::OnClicked_BTWeapon()
{
    if (!WeaponWidget && WeaponWidgetClass)
    {
        WeaponWidget = CreateWidget<UUserWidget>(GetWorld(), WeaponWidgetClass);
    }
    WeaponWidget->AddToViewport();
    RemoveFromParent();
}

void UClosetWidget::OnClicked_BTSkill()
{
    if (SkillWidget) SkillWidget->Destruct();
    SkillWidget = nullptr;

    SkillWidget = CreateWidget<UUserWidget>(GetWorld(), SkillWidgetClass);
    SkillWidget->AddToViewport();
    RemoveFromParent();
}
