// Fill out your copyright notice in the Description page of Project Settings.

#include "Games/VirusLocalPlayer.h"

void UVirusLocalPlayer::SetInputScale(float Value)
{
    InputPitchScale = Value;
    InputRollScale = Value;
    InputYawScale = Value;
}
