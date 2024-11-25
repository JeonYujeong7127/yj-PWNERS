// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SelectCharacterWidget.h"

#include "Components/Button.h"
#include "Interfaces/GGFCharacterInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Players/VirusPlayerState.h"

void USelectCharacterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ButtonCharacterMap.Add(BT_SASER, 2);
    ButtonCharacterMap.Add(BT_MELISSA, 1);
    ButtonCharacterMap.Add(BT_LEN, 3);
    ButtonCharacterMap.Add(BT_BAY, 0);

    BT_Select->OnClicked.AddDynamic(this, &USelectCharacterWidget::OnClicked_BTSelect);

    for(auto Elem : ButtonCharacterMap)
    {
        Elem.Key->OnClicked.AddDynamic(this, &USelectCharacterWidget::OnClicked_BTCharacter);
    }

    // Get reference to the player controller
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
    {
        PlayerController->SetShowMouseCursor(true);
        PlayerController->SetInputMode(FInputModeUIOnly());
    }
}

void USelectCharacterWidget::OnClicked_BTCharacter()
{
    for (auto& Elem : ButtonCharacterMap)
    {
        int32 CharacterName = Elem.Value;

        if (Elem.Key && Elem.Key->IsHovered())
        {
            SetNoSelected(CurrentSelectButton);
            SetSelected(Elem.Key);
            CurrentSelectButton = Elem.Key;
            CurrentSelectCharacterNum = Elem.Value;
            CharacterID = Elem.Value;
        }
    }
}

void USelectCharacterWidget::OnClicked_BTSelect()
{
    // 선택 캐릭터 ID 적용
    ApplyCharacterID();

    // Get reference to the player controller
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
    {
        PlayerController->SetShowMouseCursor(false);
        PlayerController->SetInputMode(FInputModeGameOnly());
    }

    // 위젯 닫기
    RemoveFromParent();
    Destruct();
}

void USelectCharacterWidget::SetSelected(UButton* SelectedButton)
{
    FButtonStyle ButtonStyle = SelectedButton->GetStyle();

    FString FilePath = "/Game/Arts/UI/SelectCharacter/character_3.character_3";
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

void USelectCharacterWidget::SetNoSelected(UButton* NotSelectedButton)
{
    if(!NotSelectedButton) return;

    FButtonStyle ButtonStyle = NotSelectedButton->GetStyle();

    FString FilePath = "/Game/Arts/UI/SelectCharacter/character.character";
    if (UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *FilePath)))
    {
        // Create a new slate brush for the normal image
        FSlateBrush NormalBrush;
        NormalBrush.SetResourceObject(Texture);

        // Set the normal image brush
        ButtonStyle.SetNormal(NormalBrush);

        // Apply the updated style to the button
        NotSelectedButton->SetStyle(ButtonStyle);
    }
}

void USelectCharacterWidget::ApplyCharacterID()
{
    // 유효성 검사
    if(CharacterID < 0) return;

    // 변수 캐싱 및 유효성 검사
    APawn* OwnerPawn = GetOwningPlayerPawn();
    if(OwnerPawn == nullptr) return;

    // 캐릭터 설정
    if(OwnerPawn->Implements<UGGFCharacterInterface>())
    {
        IGGFCharacterInterface::Execute_SetCharacter(OwnerPawn, CharacterID);
    }

    // 데이터 설정
    if(auto VirusPlayerState = Cast<AVirusPlayerState>(GetOwningPlayerState()))
    {
        VirusPlayerState->SetCharacterID(CharacterID);
    }
}
