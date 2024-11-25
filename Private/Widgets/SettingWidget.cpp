// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SettingWidget.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Characters/VirusPlayerCharacter.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "GameFramework/GameUserSettings.h"
#include "Games/VirusLocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Players/VirusPlayerController.h"
#include "Sound/SoundClass.h"

class UInputSettings;

void USettingWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 필수 값 초기화
    GameUserSettings = GEngine->GetGameUserSettings();
    PlayerCharacter = Cast<AVirusPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    PlayerController = Cast<AVirusPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
    if(LocalPlayer)
    {
        VirusLocalPlayer = Cast<UVirusLocalPlayer>(LocalPlayer);
    }

    // Get reference to the player controller
    if (PlayerController)
    {
        PlayerController->SetShowMouseCursor(true);
        PlayerController->SetInputMode(FInputModeUIOnly());

        MouseSensitivity = PlayerController->GetInputAxisValue(TEXT("Yaw"));
    }

    /*
     * 그래픽 설정
     */

    BT_VSyncOn->OnClicked.AddDynamic(this, &USettingWidget::OnClicked_BTVsyncOn);
    BT_VSyncOff->OnClicked.AddDynamic(this, &USettingWidget::OnClicked_BTVsyncOff);

    BT_NameShowOn->OnClicked.AddDynamic(this, &USettingWidget::OnClicked_BTNameShowOn);
    BT_NameShowOff->OnClicked.AddDynamic(this, &USettingWidget::OnClicked_BTNameShowOff);

    BT_GraphicLevelLow->OnClicked.AddDynamic(this, &USettingWidget::OnGraphicLevelLowClicked);
    BT_GraphicLevelMedium->OnClicked.AddDynamic(this, &USettingWidget::OnGraphicLevelMediumClicked);
    BT_GraphicLevelHigh->OnClicked.AddDynamic(this, &USettingWidget::OnGraphicLevelHighClicked);

    bIsVSyncEnabled = GEngine->GetGameUserSettings()->bUseVSync;

    // Initialize button states
    if(bIsVSyncEnabled)
    {
        UpdateButtonStates(BT_VSyncOn, BT_VSyncOff);
    }
    else
    {
        UpdateButtonStates(BT_VSyncOff, BT_VSyncOn);
    }

    if(PlayerCharacter->GetPlayerNameWidgetComponent()->IsWidgetVisible())
    {
        UpdateButtonStates(BT_NameShowOn, BT_NameShowOff);
    }
    else
    {
        UpdateButtonStates(BT_NameShowOff, BT_NameShowOn);
    }

    GraphicLevel = GameUserSettings->GetOverallScalabilityLevel();

    TArray<UButton*> Buttons;

    switch(GraphicLevel)
    {
        default:
            Buttons.Empty();
            Buttons.Add(BT_GraphicLevelMedium);
            Buttons.Add(BT_GraphicLevelHigh);
            UpdateButtonStates(BT_GraphicLevelLow, Buttons);
            break;

        case 2:
            Buttons.Empty();
            Buttons.Add(BT_GraphicLevelMedium);
            Buttons.Add(BT_GraphicLevelHigh);
            UpdateButtonStates(BT_GraphicLevelLow, Buttons);
            break;

        case 3:
            Buttons.Empty();
            Buttons.Add(BT_GraphicLevelLow);
            Buttons.Add(BT_GraphicLevelHigh);
            UpdateButtonStates(BT_GraphicLevelMedium, Buttons);
            break;

        case 4:
            Buttons.Empty();
            Buttons.Add(BT_GraphicLevelLow);
            Buttons.Add(BT_GraphicLevelMedium);
            UpdateButtonStates(BT_GraphicLevelHigh, Buttons);
            break;
    }


    /*
     * 마우스 감도 설정
     */

    S_MouseSensitivity->SetValue(VirusLocalPlayer->GetInputScale());
    S_MouseSensitivity->OnValueChanged.AddDynamic(this, &USettingWidget::OnValueChanged_SMouseSensitivity);


    /*
     * 사운드 설정
     */

    S_MasterVolume->SetValue(MasterSoundClass->Properties.Volume);
    S_BackgroundVolume->SetValue(BackgroundClass->Properties.Volume);
    S_SFXVolume->SetValue(SFXSoundClass->Properties.Volume);

    MasterVolume = MasterSoundClass->Properties.Volume;
    BackgroundVolume = BackgroundClass->Properties.Volume;
    SFXVolume = SFXSoundClass->Properties.Volume;

    S_MasterVolume->OnValueChanged.AddDynamic(this, &USettingWidget::OnValueChanged_SMasterVolume);
    S_BackgroundVolume->OnValueChanged.AddDynamic(this, &USettingWidget::OnValueChanged_SBackgroundVolume);
    S_SFXVolume->OnValueChanged.AddDynamic(this, &USettingWidget::OnValueChanged_SSFXVolume);

    BT_Select->OnClicked.AddDynamic(this, &USettingWidget::OnClicked_BTSelect);
}

void USettingWidget::NativeDestruct()
{
    Super::NativeDestruct();

    if (PlayerController)
    {
        PlayerController->SetShowMouseCursor(false);
        PlayerController->SetInputMode(FInputModeGameOnly());
    }
}

void USettingWidget::OnClicked_BTSelect()
{
    Cast<UVirusLocalPlayer>(LocalPlayer)->SetInputScale(MouseSensitivity);


    PlayerCharacter->GetPlayerNameWidgetComponent()->SetVisibility(bIsAppearNickname);
    GameUserSettings->SetVSyncEnabled(bIsVSyncEnabled);
    GameUserSettings->SetOverallScalabilityLevel(GraphicLevel);
    GameUserSettings->ApplySettings(true);
    SetVolume();

    RemoveFromParent();
    Destruct();
}

void USettingWidget::OnValueChanged_SMouseSensitivity(float Value)
{
    MouseSensitivity = Value;
    // 마우스 감도 미구현
}

void USettingWidget::OnClicked_BTVsyncOn()
{
    // Set V-Sync on and update button states
    bIsVSyncEnabled = true;
    UpdateButtonStates(BT_VSyncOn, BT_VSyncOff);
}

void USettingWidget::OnClicked_BTVsyncOff()
{
    // Set V-Sync off and update button states
    bIsVSyncEnabled = false;
    UpdateButtonStates(BT_VSyncOff, BT_VSyncOn);
}

void USettingWidget::OnClicked_BTNameShowOn()
{
    bIsAppearNickname = true;
    UpdateButtonStates(BT_NameShowOn, BT_NameShowOff);
}

void USettingWidget::OnClicked_BTNameShowOff()
{
    bIsAppearNickname = false;
    UpdateButtonStates(BT_NameShowOff, BT_NameShowOn);
}

void USettingWidget::OnGraphicLevelLowClicked()
{
    GraphicLevel = 2; // Set graphic level to low

    TArray<UButton*> Buttons;
    Buttons.Add(BT_GraphicLevelMedium);
    Buttons.Add(BT_GraphicLevelHigh);

    UpdateButtonStates(BT_GraphicLevelLow, Buttons);}

void USettingWidget::OnGraphicLevelMediumClicked()
{
    GraphicLevel = 3; // Set graphic level to medium

    TArray<UButton*> Buttons;
    Buttons.Add(BT_GraphicLevelLow);
    Buttons.Add(BT_GraphicLevelHigh);

    UpdateButtonStates(BT_GraphicLevelMedium, Buttons);
}

void USettingWidget::OnGraphicLevelHighClicked()
{
    GraphicLevel = 4; // Set graphic level to high

    TArray<UButton*> Buttons;
    Buttons.Add(BT_GraphicLevelLow);
    Buttons.Add(BT_GraphicLevelMedium);

    UpdateButtonStates(BT_GraphicLevelHigh, Buttons);
}
void USettingWidget::UpdateButtonStates(UButton* SelectedButton, TArray<UButton*> UnSelectedButtons) const
{
    // Update button images based on V-Sync state
    if (SelectedButton && UnSelectedButtons.Num() > 0)
    {
        // Set selected button image
        if (SelectedButton)
        {
            FButtonStyle SelectedButtonStyle = SelectedButton->GetStyle();
            SelectedButtonStyle.Normal.SetResourceObject(T_Selected);

            SelectedButton->SetStyle(SelectedButtonStyle);
        }

        // Set unselected button image
        if (UnSelectedButtons.Num() > 0)
        {
            for(auto UnSelectedButton : UnSelectedButtons)
            {
                FButtonStyle UnSelectedButtonStyle = UnSelectedButton->GetStyle();
                UnSelectedButtonStyle.Normal.SetResourceObject(T_UnSelected);

                UnSelectedButton->SetStyle(UnSelectedButtonStyle);
            }
        }
    }
}

void USettingWidget::UpdateButtonStates(UButton* SelectedButton, UButton* UnSelectedButton) const
{
    // Update button images based on V-Sync state
    if (SelectedButton && UnSelectedButton)
    {
        // Set selected button image
        if (SelectedButton)
        {
            FButtonStyle SelectedButtonStyle = SelectedButton->GetStyle();
            SelectedButtonStyle.Normal.SetResourceObject(T_Selected);

            SelectedButton->SetStyle(SelectedButtonStyle);
        }

        // Set unselected button image
        if (UnSelectedButton)
        {
            FButtonStyle UnSelectedButtonStyle = UnSelectedButton->GetStyle();
            UnSelectedButtonStyle.Normal.SetResourceObject(T_UnSelected);

            UnSelectedButton->SetStyle(UnSelectedButtonStyle);
        }
    }
}

void USettingWidget::OnValueChanged_SMasterVolume(float Value)
{
    MasterVolume = Value;
    BackgroundVolume = Value;
    SFXVolume = Value;

    S_BackgroundVolume->SetValue(Value);
    S_SFXVolume->SetValue(Value);
}

void USettingWidget::OnValueChanged_SBackgroundVolume(float Value)
{
    BackgroundVolume = Value;
}

void USettingWidget::OnValueChanged_SSFXVolume(float Value)
{
    SFXVolume = Value;
}

void USettingWidget::SetVolume()
{
    if (MasterSoundClass)
    {
        MasterSoundClass->Properties.Volume = MasterVolume;
    }

    if (BackgroundClass)
    {
        BackgroundClass->Properties.Volume = BackgroundVolume;
    }

    if (SFXSoundClass)
    {
        SFXSoundClass->Properties.Volume = SFXVolume;
    }
}

