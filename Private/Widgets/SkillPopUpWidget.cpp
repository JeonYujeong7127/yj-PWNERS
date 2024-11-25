// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SkillPopUpWidget.h"

#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void USkillPopUpWidget::NativeConstruct()
{
    Super::NativeConstruct();

    PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    FVector2D MousePosition;
    PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

    // Adjust the position of the widget based on mouse position
    SetPositionInViewport(FVector2d(MousePosition.X + 10.f, MousePosition.Y));
}

void USkillPopUpWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    FVector2D MousePosition;
    PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

    // Adjust the position of the widget based on mouse position
    SetPositionInViewport(FVector2d(MousePosition.X + 10.f, MousePosition.Y));
}

void USkillPopUpWidget::SetSkillData(const FGGFSkillData& InSkillData)
{
    Text_SkillName->SetText(FText::FromString(InSkillData.DisplayName.ToString()));
    Text_SkillDescription->SetText(InSkillData.Description);
}
