// Fill out your copyright notice in the Description page of Project Settings.
// 서버와 모든 클라이언트에 위젯을 생성하는 액터

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetManager.generated.h"

// TODO 위젯은 로컬 플레이어 컨트롤러에만 생성되고, 게임 모드는 서버에만 존재합니다.
// TODO 따라서 멀티 캐스트가 아니라 게임 스테이트 클래스에서 게임 결과 관련 프로퍼티를 리플리케이트하고
// TODO OnRep 메서드에서 클라이언트 각각에서 위젯 생성 후 표시하도록 하는 것이 적절합니다.
UCLASS()
class VIRUS_API AWidgetManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWidgetManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(NetMulticast, Reliable)
    void MulticastShowWidgetFunction(TSubclassOf<UUserWidget> UserWidget);

    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
};
