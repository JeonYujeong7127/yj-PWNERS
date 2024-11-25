// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/VirusStageGameState.h"

#include "Players/VirusLobbyPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Virus.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Texture2D.h"
#include "Players/VirusStagePlayerState.h"

void AVirusStageGameState::BeginPlay()
{
    Super::BeginPlay();

    ServerTime = GetServerWorldTimeSeconds();

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
    {
        for(auto PS : PlayerArray)
        {
            PCs.Add(Cast<AVirusLobbyPlayerController>(PS->GetOwningController()));
            SteamAvatars.Add(PS->GetPlayerName(), Cast<AVirusStagePlayerState>(PS)->SteamAvatar);
        }

        for(auto PC:PCs)
        {
            if(PC)
            {
                PC->bIsGameStart = true;
                if(PC->GetLocalRole() == ROLE_Authority)
                {
                    PC->GameStart();
                }
            }
        }
    }), 3.f, false);
}

void AVirusStageGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void AVirusStageGameState::Destroyed()
{
    auto& TimerManager = GetWorldTimerManager();
    if(TimerManager.IsTimerActive(FinishTimerHandle)) TimerManager.ClearTimer(FinishTimerHandle);

    Super::Destroyed();
}

void AVirusStageGameState::SetIsStageClear(bool Value)
{
    bIsStageClear = Value;
    FinishGame(bIsStageClear);
}

void AVirusStageGameState::OnRep_bIsStageClear()
{
    GetWorld()->ServerTravel(TEXT("/VirusMap/Maps/Lobby_stylize"));
}

void AVirusStageGameState::FinishGame(bool bResult)
{
    GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);

    EndTime = GetServerWorldTimeSeconds();

    StageResult.bSucceed = bResult;
    StageResult.TotalTime = EndTime - StartTime;

    // 서버 플레이어
    OnStageResultReceived.Broadcast(StageResult);

    // 타이머 설정
    auto& TimerManager = GetWorldTimerManager();
    TimerManager.SetTimer(FinishTimerHandle, this, &ThisClass::ReturnToLobby, 5.f, false);
}

void AVirusStageGameState::FloatLoadingScreen()
{
    for(auto PC:PCs)
    {
        PC->bIsLoading = true;

        NET_LOG(LogTemp, Log, TEXT("%s"), TEXT("Floating"));

        if(PC->GetLocalRole() == ROLE_Authority)
        {
            PC->FloatLoadingScreen();
        }
    }
}

void AVirusStageGameState::FloatScript()
{
    for(auto PC : PCs)
    {

    }
}


void AVirusStageGameState::OnRep_StageResult()
{
    // 클라이언트
    OnStageResultReceived.Broadcast(StageResult);
}


void AVirusStageGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, StageResult);
}

void AVirusStageGameState::ReturnToLobby()
{
    if(auto World = GetWorld())
    {
        World->ServerTravel(TEXT("/VirusMap/Maps/Lobby_stylize"));
    }
}
