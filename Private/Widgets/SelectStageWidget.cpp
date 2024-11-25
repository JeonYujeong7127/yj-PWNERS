// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SelectStageWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Games/VirusLobbyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Lobby/StartingDevice.h"

void USelectStageWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Initailize 작업
    Images.Empty();
    InGameImages.Empty();
    Texts.Empty();

    BT_Left->OnClicked.Clear();
    BT_Right->OnClicked.Clear();
    BT_GameStart->OnClicked.Clear();
    BT_ESC->OnClicked.Clear();

    Images.Add(Img_FirstStage);
    Images.Add(Img_SecondStage);
    Images.Add(Img_ThirdStage);

    InGameImages.Add(Img_FirstStageInGame);
    InGameImages.Add(Img_SecondStageInGame);
    InGameImages.Add(Img_ThirdStageInGame);

    Texts.Add(Text_FirstStage);
    Texts.Add(Text_SecondStage);
    Texts.Add(Text_ThirdStage);

    BT_Left->OnClicked.AddDynamic(this, &USelectStageWidget::Onclicked_BTLeft);
    BT_Right->OnClicked.AddDynamic(this, &USelectStageWidget::Onclicked_BTRight);
    BT_GameStart->OnClicked.AddDynamic(this, &USelectStageWidget::USelectStageWidget::OnClicked_BTGameStart);
    BT_ESC->OnClicked.AddDynamic(this, &USelectStageWidget::USelectStageWidget::Onclicked_BTESC);

    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PlayerController->SetInputMode(InputMode);

        PlayerController->bShowMouseCursor = true;
    }
}

void USelectStageWidget::NativeDestruct()
{
    Super::NativeDestruct();

    if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
        PlayerController->SetShowMouseCursor(false);
    }
}

void USelectStageWidget::OnClicked_BTGameStart()
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (!PlayerController->HasAuthority())
        {
            // 서버가 아니면 위젯을 제거합니다.
            RemoveFromParent();
            Destruct();
        }
        else
        {
            AVirusLobbyGameState* LobbyGameState = Cast<AVirusLobbyGameState>(GetWorld()->GetGameState());

            if(!LobbyGameState->bIsGameStart)
            {
                LobbyGameState->bIsGameStart = true;
                LobbyGameState->TimerStart();
                LobbyGameState->StageNum = CurrentStageNum;
            }

            TArray<AActor*> FoundActors;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStartingDevice::StaticClass(), FoundActors);

            if(FoundActors.Num() > 0)
            {
                Cast<AStartingDevice>(FoundActors[0])->SettingDisplay(CurrentStageNum);
            }

            RemoveFromParent();
        }
    }
}

void USelectStageWidget::Onclicked_BTESC()
{
    RemoveFromParent();
    Destruct();
}

void USelectStageWidget::Onclicked_BTLeft()
{
    // 스테이지 번호 로직
    CurrentStageNum--;
    if (CurrentStageNum < 1)
    {
        CurrentStageNum = 3;
    }

    UE_LOG(LogTemp, Log, TEXT("click leftStagenum: %d"), CurrentStageNum);

    // shift images left
    if (Images.Num() > 1)
    {
        UObject* LastResource = Images.Last()->GetBrush().GetResourceObject();

        for (int32 i = Images.Num() - 1; i > 0; --i)
        {
            UObject* CurrentResource = Images[i - 1]->GetBrush().GetResourceObject();
            Images[i]->SetBrushResourceObject(CurrentResource);
        }

        Images[0]->SetBrushResourceObject(LastResource);
    }

    // shift images left
    if (InGameImages.Num() > 1)
    {
        UObject* LastResource = InGameImages.Last()->GetBrush().GetResourceObject();

        for (int32 i = InGameImages.Num() - 1; i > 0; --i)
        {
            UObject* CurrentResource = InGameImages[i - 1]->GetBrush().GetResourceObject();
            InGameImages[i]->SetBrushResourceObject(CurrentResource);
        }

        InGameImages[0]->SetBrushResourceObject(LastResource);
    }

    // shift texts left
    if (Texts.Num() > 1)
    {
        FText LastText = Texts.Last()->GetText();

        for (int32 i = Texts.Num() - 1; i > 0; --i)
        {
            FText CurrentText = Texts[i - 1]->GetText();
            Texts[i]->SetText(CurrentText);
        }

        Texts[0]->SetText(LastText);
    }
}

void USelectStageWidget::Onclicked_BTRight()
{
    // 스테이지 번호 로직
    CurrentStageNum++;
    if (CurrentStageNum > 3)
    {
        CurrentStageNum = 0;
    }

    UE_LOG(LogTemp, Log, TEXT("click right Stagenum: %d"), CurrentStageNum);

    // shift images right
    if (Images.Num() > 1)
    {
        UObject* FirstResource = Images[0]->GetBrush().GetResourceObject();

        for (int32 i = 0; i < Images.Num() - 1; ++i)
        {
            UObject* CurrentResource = Images[i + 1]->GetBrush().GetResourceObject();
            Images[i]->SetBrushResourceObject(CurrentResource);
        }

        Images.Last()->SetBrushResourceObject(FirstResource);
    }

    // shift images right
    if (InGameImages.Num() > 1)
    {
        UObject* FirstResource = InGameImages[0]->GetBrush().GetResourceObject();

        for (int32 i = 0; i < InGameImages.Num() - 1; ++i)
        {
            UObject* CurrentResource = InGameImages[i + 1]->GetBrush().GetResourceObject();
            InGameImages[i]->SetBrushResourceObject(CurrentResource);
        }

        InGameImages.Last()->SetBrushResourceObject(FirstResource);
    }

    // shift texts right
    if (Texts.Num() > 1)
    {
        FText FirstText = Texts[0]->GetText();

        for (int32 i = 0; i < Texts.Num() - 1; ++i)
        {
            FText CurrentText = Texts[i + 1]->GetText();
            Texts[i]->SetText(CurrentText);
        }

        Texts.Last()->SetText(FirstText);
    }
}
