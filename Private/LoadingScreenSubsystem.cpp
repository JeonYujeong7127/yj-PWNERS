// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreenSubsystem.h"
#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"
#include "Games/VirusGameState.h"
#include "Virus.h"
#include "Games/VirusStageGameState.h"

ULoadingScreenSubsystem::ULoadingScreenSubsystem()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> LoadingWidgetAsset(TEXT("/Game/Virus/UI/WBP_Loading"));

    if (LoadingWidgetAsset.Succeeded())
        LoadingWidgetClass = LoadingWidgetAsset.Class;
}

void ULoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    UE_LOG(LogTemp, Log, TEXT("LoadingScreenSubsystem Initialize"));

    Super::Initialize(Collection);

    CreateMoviePlayer();
    FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ULoadingScreenSubsystem::OnPreLoadMap);
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ULoadingScreenSubsystem::OnPostLoadMap);
}

void ULoadingScreenSubsystem::OnPreLoadMap(const FString& InMapName)
{
    const auto LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidgetClass);
    const TSharedRef<SWidget> LoadingSWidgetPtr = LoadingWidget->TakeWidget();

    FLoadingScreenAttributes LoadingScreen;
    LoadingScreen.WidgetLoadingScreen = LoadingSWidgetPtr;
    LoadingScreen.bAllowInEarlyStartup = false;
    LoadingScreen.PlaybackType = MT_Normal;
    LoadingScreen.bAllowEngineTick = false;
    LoadingScreen.bWaitForManualStop = false;
    LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
    LoadingScreen.MinimumLoadingScreenDisplayTime = 2.f;

    if(IGameMoviePlayer* MoviePlayer = GetMoviePlayer())
    {
        MoviePlayer->SetupLoadingScreen(LoadingScreen);
    }
}

void ULoadingScreenSubsystem::OnPostLoadMap(UWorld* LoadedWorld)
{
    if(AVirusStageGameState* StageGameState = Cast<AVirusStageGameState>(LoadedWorld->GetGameState()))
    {
        StageGameState->FloatLoadingScreen();
    }
}
