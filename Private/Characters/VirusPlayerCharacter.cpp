// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/VirusPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerState.h"
#include "Players/VirusStagePlayerController.h"
#include "Widgets/PlayerNameWidget.h"

AVirusPlayerCharacter::AVirusPlayerCharacter()
{
    /* PlayerNameWidgetComponent */
    PlayerNameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("PlayerNameWidgetComponent");
    PlayerNameWidgetComponent->SetupAttachment(RootComponent);
    PlayerNameWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PlayerNameWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    PlayerNameWidgetComponent->SetDrawAtDesiredSize(true);
    PlayerNameWidgetComponent->SetVisibility(false);

    /* FirstPersonCamera */
    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(RootComponent);
    FirstPersonCamera->SetRelativeLocation(FVector(-10, 0, 75));

    /* 기본 에셋 설정 */
    static ConstructorHelpers::FClassFinder<UUserWidget> PlayerNameWidgetComponentFinder(TEXT("/Game/Virus/UI/WBP_PlayerName"));
    if (PlayerNameWidgetComponentFinder.Succeeded())
    {
        PlayerNameWidgetComponent->SetWidgetClass(PlayerNameWidgetComponentFinder.Class);
    }
}

void AVirusPlayerCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    PlayerNameWidgetComponent->InitWidget();
    PlayerNameWidgetComponent->SetRelativeLocation(FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
}

void AVirusPlayerCharacter::NotifyControllerChanged()
{
    Super::NotifyControllerChanged();

    // Old Controller
    if(PreviousController && PreviousController->IsLocalPlayerController())
    {
        auto PreviousLocalPlayerController = Cast<APlayerController>(PreviousController);
        PreviousLocalPlayerController->ClearAudioListenerOverride();
    }

    // New Controller
    if(Controller && Controller->IsLocalPlayerController())
    {
        auto LocalPlayerController = Cast<APlayerController>(Controller);
        LocalPlayerController->SetAudioListenerOverride(GetFirstPersonCamera(), FVector::ZeroVector, FRotator::ZeroRotator);
    }
}

void AVirusPlayerCharacter::OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
    Super::OnPlayerStateChanged(NewPlayerState, OldPlayerState);

    UpdatePlayerName(NewPlayerState);
}

void AVirusPlayerCharacter::OnDead_Implementation()
{
    Super::OnDead_Implementation();

    if(AVirusStagePlayerController* StageController = Cast<AVirusStagePlayerController>(Controller))
    {
        StageController->bIsDie = true;
        StageController->ShowDieWidget();
    }

    if(auto PlayerController = Cast<APlayerController>(Controller))
    {
        PlayerController->ChangeState(NAME_Spectating);
    }
}

void AVirusPlayerCharacter::UpdatePlayerName(APlayerState* NewPlayerState)
{
    if(NewPlayerState)
    {
        // TODO 리팩토링
        if(auto PlayerNameWidget = Cast<UPlayerNameWidget>(PlayerNameWidgetComponent->GetWidget()))
        {
            PlayerNameWidget->SetPlayerName(NewPlayerState->GetPlayerName());
        }
    }

    GetPlayerNameWidgetComponent()->SetVisibility(NewPlayerState != nullptr);
}
