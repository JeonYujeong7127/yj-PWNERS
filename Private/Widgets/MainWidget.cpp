// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainWidget::NativeConstruct()
{
    Super::NativeConstruct();
    BTStart->OnClicked.AddDynamic(this, &UMainWidget::OnBTStartClicked);
    BTQuit->OnClicked.AddDynamic(this, &UMainWidget::OnBTQuitClicked);
}

void UMainWidget::OnBTStartClicked()
{
    CreateSession();
    UGameplayStatics::OpenLevel(GetWorld(), *LevelName, true, "Listen");
}

void UMainWidget::OnBTQuitClicked()
{
    FGenericPlatformMisc::RequestExit(false);
}
