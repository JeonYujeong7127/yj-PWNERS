// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScriptFloor.generated.h"

UCLASS()
class VIRUS_API AScriptFloor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AScriptFloor();

    UPROPERTY()
    class UBoxComponent* CollisionMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


    bool bStartScript = false;

    void PrintScript();
    void SetScript(struct FScriptData* ScriptData);

    UFUNCTION(BlueprintPure, Category = "Color Conversion")
    static FLinearColor HexToLinearColor(const FText& ColorText);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString NavigationID;

    // 이 Navigation_ID에 해당하는 스크립트 모음
    TArray<struct FScriptData*> Scripts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* ScriptDataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* SpeakerDataTable;

    TArray<struct FSpeakerData*> SpeakerRows;

private:
    UPROPERTY()
    class AVirusPlayerController* PC;
};
