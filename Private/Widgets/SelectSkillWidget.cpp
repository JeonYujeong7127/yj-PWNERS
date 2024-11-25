// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/SelectSkillWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Data/GGFSkillDataSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Players/VirusPlayerState.h"
#include "Widgets/SkillPopUpWidget.h"

void USelectSkillWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    UE_LOG(LogTemp, Log, TEXT("NativePreConstruct"));

    ButtonSkillIDMap.Empty();
    ButtonSkillNameMap.Empty();
    PrimarySkillID = 0;
    SecondarySkillID = 1;
    SelectedPrimarySkillButton = nullptr;
    SelectedSecondarySkillButton = nullptr;
    SelectedSkillButton = nullptr;
    SkillDefinitionIDMap.Empty();

    BT_Select->OnClicked.Clear();
    BT_ResetSkill->OnClicked.Clear();
    BT_QSkill->OnClicked.Clear();
    BT_ESkill->OnClicked.Clear();

    // TODO 서브 위젯 클래스로 분리
    /* 버튼 별 스킬 ID 맵 하드코딩 */
    ButtonSkillIDMap.Add(0, BT_SkillPower);
    ButtonSkillIDMap.Add(1, BT_SkillFloorHeal);
    ButtonSkillIDMap.Add(2, BT_SkillDark);
    ButtonSkillIDMap.Add(3, BT_SkillShield);
    ButtonSkillIDMap.Add(4, BT_SkillHeal);
    ButtonSkillIDMap.Add(5, BT_SkillLighting);
    ButtonSkillIDMap.Add(6, BT_SkillTurret);

    /*ButtonSkillIDMap.Add(-1, BT_SkillAggro);
    ButtonSkillIDMap.Add(-1, BT_SkillBang);
    ButtonSkillIDMap.Add(-1, BT_SkillBondage);
    ButtonSkillIDMap.Add(-1, BT_SkillPurification);
    ButtonSkillIDMap.Add(-1, BT_SkillSacrifice);
    ButtonSkillIDMap.Add(-1, BT_SkillSalvation);
    ButtonSkillIDMap.Add(-1, BT_SkillSleeping);
    ButtonSkillIDMap.Add(-1, BT_SkillSpupping);*/

    /* 버튼 별 스킬 이름 하드 코딩 */

    ButtonSkillNameMap.Add(BT_SkillAggro, "Aggro");
    ButtonSkillNameMap.Add(BT_SkillBang, "Bang");
    ButtonSkillNameMap.Add(BT_SkillBondage, "Bondage");
    ButtonSkillNameMap.Add(BT_SkillDark, "Dark");
    ButtonSkillNameMap.Add(BT_SkillHeal, "Heal");
    ButtonSkillNameMap.Add(BT_SkillLighting, "Lighting");
    ButtonSkillNameMap.Add(BT_SkillPower, "Power");
    ButtonSkillNameMap.Add(BT_SkillPurification, "Purification");
    ButtonSkillNameMap.Add(BT_SkillSacrifice, "Sacrifice");
    ButtonSkillNameMap.Add(BT_SkillSalvation, "Salvation");
    ButtonSkillNameMap.Add(BT_SkillShield, "Shield");
    ButtonSkillNameMap.Add(BT_SkillSleeping, "Sleeping");
    ButtonSkillNameMap.Add(BT_SkillSpupping, "Spupping");
    ButtonSkillNameMap.Add(BT_SkillTurret, "Turret");
    ButtonSkillNameMap.Add(BT_SkillFloorHeal, "FloorHeal");

    /* 버튼 이벤트 바인딩 */

    BT_Select->OnClicked.AddDynamic(this, &USelectSkillWidget::OnClicked_BTSelect);
    BT_ResetSkill->OnClicked.AddDynamic(this, &USelectSkillWidget::OnClicked_BTResetSkill);
    BT_QSkill->OnClicked.AddDynamic(this, &USelectSkillWidget::OnClicked_BTQSkill);
    BT_ESkill->OnClicked.AddDynamic(this, &USelectSkillWidget::OnClicked_BTESkill);

    for(const auto& [SkillID, Button] : ButtonSkillIDMap)
    {
        Button->OnClicked.AddDynamic(this, &USelectSkillWidget::OnClicked_BTSkill);
        Button->OnHovered.AddDynamic(this, &USelectSkillWidget::OnHovered_BTSkill);
        Button->OnUnhovered.AddDynamic(this, &USelectSkillWidget::OnUnHovered_BTSkill);
    }

    BT_ESC->OnClicked.AddDynamic(this, &USelectSkillWidget::OnClicked_BTEsc);
}

void USelectSkillWidget::NativeConstruct()
{
    Super::NativeConstruct();

    /* 데이터 읽어오기 */

    // 데이터 테이블
    if(auto SkillDataSubsystem = GetGameInstance()->GetSubsystem<UGGFSkillDataSubsystem>())
    {
        // 하드 코딩
        for (int32 SkillID = 0; SkillID < 7; ++SkillID)
        {
            if(auto SkillDefinition = SkillDataSubsystem->GetDefinition(SkillID))
            {
                SkillDefinitionIDMap.Emplace(SkillID, SkillDefinition);
            }
        }
    }

    // 플레이어 스테이트
    if(auto VirusPlayerState = Cast<AVirusPlayerState>(GetOwningPlayerState()))
    {
        PrimarySkillID = VirusPlayerState->GetPrimarySkillID();
        SecondarySkillID = VirusPlayerState->GetSecondarySkillID();

        // PrimarySkill
        {
            SelectedPrimarySkillButton = ButtonSkillIDMap[PrimarySkillID];
            SetSelected(SelectedPrimarySkillButton);
            FString SkillName = ButtonSkillNameMap[SelectedPrimarySkillButton].ToString();
            SetImageFromFile(Img_FirstSkill, SkillName);
        }

        // SecondarySkill
        {
            SelectedSecondarySkillButton = ButtonSkillIDMap[SecondarySkillID];
            SetSelected(SelectedSecondarySkillButton);
            FString SkillName = ButtonSkillNameMap[SelectedSecondarySkillButton].ToString();
            SetImageFromFile(Img_SecondSkill, SkillName);
        }
    }
}

void USelectSkillWidget::NativeDestruct()
{
    Super::NativeDestruct();
}

void USelectSkillWidget::OnClicked_BTSkill()
{
    for (const auto& [SkillID, Button] : ButtonSkillIDMap)
    {
        if (Button && Button->IsHovered())
        {
            FString SkillName = ButtonSkillNameMap[Button].ToString();
            FString ImagePath = "/Game/Arts/UI/skill_icon/" + SkillName + "." + SkillName;

            // 이미 선택한 스킬을 선택하는 경우
            if(PrimarySkillID == SkillID)
            {
                PrimarySkillID = -1;
                SetImageFromFile(Img_FirstSkill, "NONE");
                SetNoSelected(Button);

                return;
            }
            else if(SecondarySkillID == SkillID)
            {
                SecondarySkillID = -1;
                SetImageFromFile(Img_SecondSkill, "NONE");
                SetNoSelected(Button);

                return;
            }

            // 새로운 스킬이 선택된 경우
            if (SelectedSkillButton == BT_QSkill)
            {
                PrimarySkillID = SkillID;
                SetImageFromFile(Img_FirstSkill, SkillName);
                SetSelected(Button);
                PlayTriangleAnimation(TEXT("Q"), false);
                SelectedSkillButton = nullptr;

                // 기존에 선택된 스킬 슬롯 비활성화 및 새로 선택된 스킬 슬롯 활성화
                SetNoSelected(SelectedPrimarySkillButton);
                SelectedPrimarySkillButton = Button;
                SetSelected(SelectedPrimarySkillButton);

                return;
            }
            else if (SelectedSkillButton == BT_ESkill)
            {
                SecondarySkillID = SkillID;
                SetImageFromFile(Img_SecondSkill, SkillName);
                SetSelected(Button);
                PlayTriangleAnimation(TEXT("E"), false);
                SelectedSkillButton = nullptr;

                // 기존에 선택된 스킬 슬롯 비활성화 및 새로 선택된 스킬 슬롯 활성화
                SetNoSelected(SelectedSecondarySkillButton);
                SelectedSecondarySkillButton = Button;
                SetSelected(SelectedSecondarySkillButton);

                return;
            }
        }
    }
}

void USelectSkillWidget::OnClicked_BTSelect()
{
    // 스킬 ID 적용
    if(auto VirusPlayerState = Cast<AVirusPlayerState>(GetOwningPlayerState()))
    {
        if(PrimarySkillID >= 0 && VirusPlayerState->GetPrimarySkillID() != PrimarySkillID)
        {
            VirusPlayerState->SetPrimarySkillID(PrimarySkillID);
        }

        if(SecondarySkillID >= 0 && VirusPlayerState->GetSecondarySkillID() != SecondarySkillID)
        {
            VirusPlayerState->SetSecondarySkillID(SecondarySkillID);
        }
    }

    RemoveFromParent();
    Destruct();
}

void USelectSkillWidget::OnClicked_BTQSkill()
{
    // Q를 선택한 상태에서 다시 선택했을 경우 (토글 해제)
    if(SelectedSkillButton == BT_QSkill)
    {
        SelectedSkillButton = nullptr;
        PlayTriangleAnimation(TEXT("Q"), false);
    }
    else // 토글 선택
    {
        SelectedSkillButton = BT_QSkill;
        PlayTriangleAnimation(TEXT("Q"), true);
    }
}

void USelectSkillWidget::OnClicked_BTESkill()
{
    if(SelectedSkillButton == BT_ESkill)
    {
        SelectedSkillButton = nullptr;
        PlayTriangleAnimation(TEXT("E"), false);
    }
    else
    {
        SelectedSkillButton = BT_ESkill;
        PlayTriangleAnimation(TEXT("E"), true);
    }
}

void USelectSkillWidget::OnClicked_BTResetSkill()
{
    SelectedSkillButton = nullptr;

    PlayTriangleAnimation(TEXT("Q"), false);
    PlayTriangleAnimation(TEXT("E"), false);

    if(PrimarySkillID >= 0)
    {
        SetNoSelected(*ButtonSkillIDMap.Find(PrimarySkillID));
        PrimarySkillID = -1;
        SetImageFromFile(Img_FirstSkill, "NONE");
    }

    if(SecondarySkillID >= 0)
    {
        SetNoSelected(*ButtonSkillIDMap.Find(SecondarySkillID));
        SecondarySkillID = -1;
        SetImageFromFile(Img_SecondSkill, "NONE");
    }
}

void USelectSkillWidget::OnHovered_BTSkill()
{
    UE_LOG(LogTemp, Log, TEXT("Hover!"));
    if(!bIsHovered)
    {
        for (const auto& [SkillID, Button] : ButtonSkillIDMap)
        {
            FString SkillName = ButtonSkillNameMap[Button].ToString();

            if (Button && Button->IsHovered())
            {
                if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
                {
                    bIsHovered = true;
                    FVector2D MousePosition;
                    PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

                    if (!PopUpWidgets.Contains(SkillID))
                    {
                        if(SkillDefinitionIDMap.Contains(SkillID))
                        {
                            auto PopUpWidget = CreateWidget<USkillPopUpWidget>(GetWorld(), PopUpWidgetClass);
                            PopUpWidget->SetSkillData(SkillDefinitionIDMap[SkillID]->GetData());

                            PopUpWidgets.Emplace(SkillID, PopUpWidget);
                        }
                    }

                    if (PopUpWidgets.Contains(SkillID) && PopUpWidgets[SkillID])
                    {
                        PopUpWidgets[SkillID]->AddToViewport();
                    }
                }
            }
        }
    }
}

void USelectSkillWidget::OnUnHovered_BTSkill()
{
    if(!bIsHovered) return;
    bIsHovered = false;

    for (const auto& [SkillID, PopupWidget] : PopUpWidgets)
    {
        if(PopupWidget->IsInViewport())
        {
            PopupWidget->RemoveFromParent();
            break;
        }
    }
}

void USelectSkillWidget::OnClicked_BTEsc()
{
    this->RemoveFromParent();
    this->Destruct();
}

void USelectSkillWidget::SetImageFromFile(UImage* ImageWidget, const FString& SkillName)
{
    if (!ImageWidget) return;
    FString FilePath = "/Game/Arts/UI/skill_icon/" + SkillName + "." + SkillName;

    // NONE이 들어온 경우 이미지 초기화
    if(*SkillName == FString("NONE"))
    {
        ImageWidget->SetOpacity(0.f);
        return;
    }

    if (UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *FilePath)))
    {
        // Set the texture to the ImageWidget]
        ImageWidget->SetOpacity(1.f);
        ImageWidget->SetBrushFromTexture(Texture);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load texture from path: %s"), *FilePath);
    }
}

void USelectSkillWidget::SetSelected(UButton* SelectedButton)
{
    if(SelectedButton)
    {
        FButtonStyle ButtonStyle = SelectedButton->GetStyle();

        FString FilePath = "/Game/Arts/UI/skill/skilltree3.skilltree3";
        if (UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *FilePath)))
        {
            // Create a new slate brush for the normal image
            FSlateBrush NormalBrush;
            NormalBrush.SetResourceObject(Texture);

            // Set the normal image brush
            ButtonStyle.SetNormal(NormalBrush);

            // Apply the updated style to the button
            SelectedButton->SetStyle(ButtonStyle);
        }
    }
}

void USelectSkillWidget::SetNoSelected(UButton* SelectedButton)
{
    if(SelectedButton)
    {
        FButtonStyle ButtonStyle = SelectedButton->GetStyle();

        FString FilePath = "/Game/Arts/UI/skill/skilltree2.skilltree2";
        if (UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *FilePath)))
        {
            // Create a new slate brush for the normal image
            FSlateBrush NormalBrush;
            NormalBrush.SetResourceObject(Texture);

            // Set the normal image brush
            ButtonStyle.SetNormal(NormalBrush);

            // Apply the updated style to the button
            SelectedButton->SetStyle(ButtonStyle);
        }
    }
}

void USelectSkillWidget::PlayTriangleAnimation(const FString& Triangle, bool bIsPlay)
{
    if(bIsPlay)
    {
        if (Triangle == "Q")
        {
            StopAnimation(EMovingTriangle);
            Img_ETriangle->SetOpacity(0.f);
            PlayAnimation(QMovingTriangle, 0, 0);
            Img_QTriangle->SetOpacity(1.f);
        }
        else if (Triangle == "E")
        {
            StopAnimation(QMovingTriangle);
            Img_QTriangle->SetOpacity(0.f);
            PlayAnimation(EMovingTriangle, 0, 0);
            Img_ETriangle->SetOpacity(1.f);
        }
    }
    else
    {
        if (Triangle == "Q")
        {
            StopAnimation(QMovingTriangle);
            Img_QTriangle->SetOpacity(0.f);
        }
        else if (Triangle == "E")
        {
            StopAnimation(EMovingTriangle);
            Img_ETriangle->SetOpacity(0.f);
        }
    }
}
