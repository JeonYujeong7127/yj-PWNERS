// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ScriptFloor.h"

#include "Components/BoxComponent.h"
#include "Players/VirusLobbyPlayerController.h"
#include "Data/ScriptDataTableRow.h"
#include "Kismet/KismetStringLibrary.h"
#include "Widgets/ScriptWidget.h"

// Sets default values
AScriptFloor::AScriptFloor()
{
    CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
    CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AScriptFloor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AScriptFloor::BeginPlay()
{
	Super::BeginPlay();

    TArray<FScriptData*> ScriptRows;
    ScriptDataTable->GetAllRows(*FString("ScriptDataTable"), ScriptRows);

    for(const auto& Row : ScriptRows)
    {
        if(Row->Navigation_ID == NavigationID)
        {
            Scripts.Add(Row);
        }
    }

    SpeakerDataTable->GetAllRows(*FString("SpeakerDataTable"), SpeakerRows);
}

void AScriptFloor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(!bStartScript)
    {
        if(APawn* OtherPawn = Cast<APawn>(OtherActor))
        {
            if(OtherPawn->IsPlayerControlled())
            {
                PC = Cast<AVirusPlayerController>(GetWorld()->GetFirstPlayerController());
                PC->FloatScript();
                PrintScript();
                bStartScript = true;
            }
        }
    }
}

void AScriptFloor::PrintScript()
{
    UE_LOG(LogTemp, Log, TEXT("PrintScript Start, Script Num: %d"), Scripts.Num());

    float AccumulatedTime = 1.f;
    TArray<FTimerHandle> TimerHandles;
    int32 CurrentNum = 1;

    for(auto Script : Scripts)
    {
        FScriptData* LocalScript = Script;
        FTimerHandle ScriptTimerHandle;
        TimerHandles.Add(ScriptTimerHandle);

        GetWorld()->GetTimerManager().SetTimer(
            TimerHandles.Last(), // Get the reference to the last handle
            [this, LocalScript, CurrentNum]()
            {
                SetScript(LocalScript);
                PC->ScriptWidget->SetScriptStart();

                if(CurrentNum == Scripts.Num())
                {
                    FTimerHandle TempHandle;
                    GetWorld()->GetTimerManager().SetTimer(TempHandle, FTimerDelegate::CreateLambda([&]
                    {
                        PC->ScriptWidget->RemoveFromParent();
                    }), LocalScript->Duration, false);
                }
            },
            AccumulatedTime,
            false
        );
        AccumulatedTime += Script->Duration;

        CurrentNum++;
    }
}

void AScriptFloor::SetScript(FScriptData* ScriptData)
{
    for(auto Speaker : SpeakerRows)
    {
        if(ScriptData->Speaker_ID == Speaker->ID)
        {
            PC->ScriptWidget->SetSpeakerColor(HexToLinearColor(FText::FromString(Speaker->Color)));
            PC->ScriptWidget->SetSpeakerText(Speaker->Name);
        }
    }

    PC->ScriptWidget->SetScriptText(ScriptData->Script);
}

FLinearColor AScriptFloor::HexToLinearColor(const FText& ColorText)
{
    FString ColorString = ColorText.ToString();
    FLinearColor Result;

    if (ColorString.StartsWith("#"))
    {
        ColorString.RemoveAt(0); // Remove the '#' character

        // Convert the remaining string to FColor
        int32 R = FParse::HexNumber(*ColorString.Mid(0, 2));
        int32 G = FParse::HexNumber(*ColorString.Mid(2, 2));
        int32 B = FParse::HexNumber(*ColorString.Mid(4, 2));

        FLinearColor ParsedColor = FLinearColor(R, G, B, 1);
        Result = ParsedColor;
    }
    else
    {
        Result = FLinearColor::Red;
    }

    return Result;
}

