// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomNameWidgetActor.h"
#include "RoomName.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values
ARoomNameWidgetActor::ARoomNameWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root= CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	RoomNameUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));
	RoomNameUI->SetupAttachment(Root);


}

// Called when the game starts or when spawned
void ARoomNameWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	if (RoomNameUI)
	{
		Cast<URoomName>(RoomNameUI->GetWidget())->nameActor = this;
	}
}

// Called every frame
void ARoomNameWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

