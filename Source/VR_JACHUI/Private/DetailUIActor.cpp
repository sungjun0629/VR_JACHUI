// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailUIActor.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "FurnitureInformationUI.h"

// Sets default values
ADetailUIActor::ADetailUIActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetailUIWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DetailUIWidget"));
	DetailUIWidget->SetupAttachment(RootComponent);
	//DetailUIWidget->SetWidgetClass(UFurnitureInformationUI::StaticClass());
	//DetailUIWidget->SetRelativeLocation(FVector(0));

}

// Called when the game starts or when spawned
void ADetailUIActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADetailUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

