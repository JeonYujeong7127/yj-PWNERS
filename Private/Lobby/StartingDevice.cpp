// Fill out your copyright notice in the Description page of Project Settings.

#include "Lobby/StartingDevice.h"

#include "Net/UnrealNetwork.h"

AStartingDevice::AStartingDevice()
{
    DisplayMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dynamic Screen Mesh"));
    DisplayMeshComponent->SetupAttachment(RootComponent);

    BigDisplayMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Big Dynamic Screen Mesh"));
    BigDisplayMeshComponent->SetupAttachment(RootComponent);
}

void AStartingDevice::BeginPlay()
{
    Super::BeginPlay();
}

void AStartingDevice::SettingDisplay(int32 Num)
{
    StageNum = Num;

    switch(StageNum)
    {
        case(1):
            DisplayMeshComponent->SetMaterial(0, Display_Stage1);
            BigDisplayMeshComponent->SetMaterial(0, Display_Stage1);
            break;

        case(2):
            DisplayMeshComponent->SetMaterial(0, Display_Stage2);
            BigDisplayMeshComponent->SetMaterial(0, Display_Stage2);
            break;

        default:
            DisplayMeshComponent->SetMaterial(0, Display_None);
            BigDisplayMeshComponent->SetMaterial(0, Display_None);
            break;
    }
}

void AStartingDevice::OnRep_IsStageNumChanged()
{
    switch(StageNum)
    {
        case(1):
            DisplayMeshComponent->SetMaterial(0, Display_Stage1);
            BigDisplayMeshComponent->SetMaterial(0, Display_Stage1);
            break;

        case(2):
            DisplayMeshComponent->SetMaterial(0, Display_Stage2);
            BigDisplayMeshComponent->SetMaterial(0, Display_Stage2);
            break;

        default:
            DisplayMeshComponent->SetMaterial(0, Display_None);
            BigDisplayMeshComponent->SetMaterial(0, Display_None);
            break;
    }
}

void AStartingDevice::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AStartingDevice, StageNum);
}
