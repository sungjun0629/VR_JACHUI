// Fill out your copyright notice in the Description page of Project Settings.


#include "GoingMyRoomActor.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values
AGoingMyRoomActor::AGoingMyRoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	GoingRoomUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));
	GoingRoomUI->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGoingMyRoomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoingMyRoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

