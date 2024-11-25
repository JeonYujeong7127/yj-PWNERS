// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingWidget.generated.h"

/**
 *
 */
UCLASS()
class VIRUS_API USettingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Called when the widget is created
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundClass* MasterSoundClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundClass* BackgroundClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundClass* SFXSoundClass;

protected:
    UPROPERTY()
    class AVirusPlayerController* PlayerController;

    UPROPERTY()
    class AVirusPlayerCharacter* PlayerCharacter;

    UPROPERTY()
    class UGameUserSettings* GameUserSettings;

    UPROPERTY()
    class ULocalPlayer* LocalPlayer;

    UPROPERTY()
    class UVirusLocalPlayer* VirusLocalPlayer;

    // 각종 설정값들
    float MouseSensitivity = - 1.f;
    bool bIsAppearNickname = false;
    bool bIsVSyncEnabled = false;

    // 오디오 볼륨 설정값
    float BackgroundVolume = -1.f;
    float MasterVolume = -1.f;
    float SFXVolume = -1.f;

    // 2: Low, 3: Medium, 4: High
    int8 GraphicLevel = -1;

    UPROPERTY(meta = (BindWidget))
    class UButton* BT_Select;

    UFUNCTION()
    void OnClicked_BTSelect();

    UPROPERTY(meta = (BindWidget))
    class USlider* S_MouseSensitivity;

    UFUNCTION()
    void OnValueChanged_SMouseSensitivity(float Value);

    // Reference to V-Sync on and off buttons
    UPROPERTY(meta = (BindWidget))
    class UButton* BT_VSyncOn;

    UPROPERTY(meta = (BindWidget))
    class UButton* BT_VSyncOff;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UTexture2D* T_UnSelected;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UTexture2D* T_Selected;

    // Function to handle button clicks
    UFUNCTION()
    void OnClicked_BTVsyncOn();

    UFUNCTION()
    void OnClicked_BTVsyncOff();

    UPROPERTY(meta = (BindWidget))
    UButton* BT_NameShowOn;

    UPROPERTY(meta = (BindWidget))
    UButton* BT_NameShowOff;

    UFUNCTION()
    void OnClicked_BTNameShowOn();

    UFUNCTION()
    void OnClicked_BTNameShowOff();

    UPROPERTY(meta = (BindWidget))
    class UButton* BT_GraphicLevelLow;

    UPROPERTY(meta = (BindWidget))
    class UButton* BT_GraphicLevelMedium;

    UPROPERTY(meta = (BindWidget))
    class UButton* BT_GraphicLevelHigh;

    // Function to handle button clicks
    UFUNCTION()
    void OnGraphicLevelLowClicked();

    UFUNCTION()
    void OnGraphicLevelMediumClicked();

    UFUNCTION()
    void OnGraphicLevelHighClicked();

    // Update button states based on current selection
    void UpdateButtonStates(UButton* SelectedButton, TArray<UButton*> UnSelectedButtons) const;

    // Update button states based on current selection
    void UpdateButtonStates(UButton* SelectedButton, UButton* UnSelectedButton) const;

    UPROPERTY(meta = (BindWidget))
    class USlider* S_MasterVolume;

    UFUNCTION()
    void OnValueChanged_SMasterVolume(float Value);

    UPROPERTY(meta = (BindWidget))
    class USlider* S_BackgroundVolume;

    UFUNCTION()
    void OnValueChanged_SBackgroundVolume(float Value);

    UPROPERTY(meta = (BindWidget))
    class USlider* S_SFXVolume;

    UFUNCTION()
    void OnValueChanged_SSFXVolume(float Value);



private:
    void SetVolume();
};
