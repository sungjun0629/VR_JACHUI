// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureInformationUIActor.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values
AFurnitureInformationUIActor::AFurnitureInformationUIActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	InformationUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));
	InformationUI->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AFurnitureInformationUIActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFurnitureInformationUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

