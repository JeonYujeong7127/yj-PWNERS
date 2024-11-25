// Fill out your copyright notice in the Description page of Project Settings.

#include "Games/VirusLobbyGameState.h"

#include "Players/VirusLobbyPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

void AVirusLobbyGameState::BeginPlay()
{
    Super::BeginPlay();
    ServerTime = GetServerWorldTimeSeconds();
}

void AVirusLobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, bIsAllReady);
}

void AVirusLobbyGameState::EnterToStage()
{
    GetWorld()->GetTimerManager().ClearTimer(GlobalHandle);
    GetWorld()->GetTimerManager().ClearTimer(NormalHandle);

    if(true)
    {
        for(auto PC : PCs)
        {
            PC->bIsLoading = true;

            if(PC->GetLocalRole() == ROLE_Authority)
            {
                // PC->StageTimerStart();
                // 3 스테이지 이상 미구현
                UE_LOG(LogTemp, Log, TEXT("Stagenum: %d"), StageNum);

                if(StageNum > 2)
                {
                    return;
                }

                GetWorld()->ServerTravel(LevelNames[StageNum - 1]);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Stage 2, 3 is not generated"));
    }
}

void AVirusLobbyGameState::TimerStart()
{
    // Timer Start Replicate
    for(auto PS : PlayerArray)
    {
        AVirusLobbyPlayerController* PC = Cast<AVirusLobbyPlayerController>(PS->GetPlayerController());
        PCs.Add(PC);
        PC->bIsTimerStart = true;
        if(PC->GetLocalRole() == ENetRole::ROLE_Authority) PC->TimerStart();
    }

    // n초간 모두 준비됐는지 체크하며 모두 준비됐을 경우 5초 후 시작(일반 시작)
    GetWorld()->GetTimerManager().SetTimer(NormalHandle, FTimerDelegate::CreateLambda([&]
    {
        PassedSeconds += CheckSecond;

        for(auto PC : PCs)
        {
            if(PC->bIsReady)
            {
                bIsAllReady = true;
            }
            else
            {
                bIsAllReady = false;
                PassedSecondAfterAllReady = 0;
                break;
            }
        }

        if(bIsAllReady)
        {
            PassedSecondAfterAllReady += CheckSecond;
            for(auto PC : PCs)
            {
                PC->bIsAllReady = true;
                if(PC->HasAuthority()) PC->TimerAllReady();
            }

            if(PassedSecondAfterAllReady == MustPassSecondAfterAllReady)
            {
                EnterToStage();
            }
        }
        else
        {
            PassedSecondAfterAllReady = 0.0f;
            for(auto PC : PCs)
            {
                PC->bIsAllReady = false;
                if(PC->HasAuthority()) PC->TimerNotReady();
            }
        }
    }), CheckSecond, true);

    // 3분 카운트 시작(강제 시작)
    GetWorld()->GetTimerManager().SetTimer(GlobalHandle, FTimerDelegate::CreateLambda([&]
    {
        EnterToStage();
    }), TimeOutSecond, false);
}

void AVirusLobbyGameState::OnRep_bIsAllReady()
{
    for(auto PS : PlayerArray)
    {
        Cast<AVirusLobbyPlayerController>(PS->GetPlayerController())->bIsTimerStart = true;
    }
}
