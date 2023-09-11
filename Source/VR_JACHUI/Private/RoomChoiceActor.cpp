// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomChoiceActor.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "RoomChoiceWidget.h"

// Sets default values
ARoomChoiceActor::ARoomChoiceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Choice = CreateDefaultSubobject<UWidgetComponent>(TEXT("ChoiceWidget"));
	RootComponent = Choice;
	Choice->SetWidgetClass(roomChoice_Widget);
	Choice->SetDrawSize(FVector2D(2000,1200));
}

// Called when the game starts or when spawned
void ARoomChoiceActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomChoiceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

