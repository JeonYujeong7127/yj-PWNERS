// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ScriptDataTableRow.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FScriptData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Navigation_ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Script_no;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Script_Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Speaker_ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Script;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Duration;
};

USTRUCT(BlueprintType)
struct FSpeakerData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> Portrait;
};

UCLASS()
class VIRUS_API UScriptDataTableRow : public UDataTable
{
	GENERATED_BODY()

};
