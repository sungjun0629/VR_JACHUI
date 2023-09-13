// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureFavoriteActor.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values
AFurnitureFavoriteActor::AFurnitureFavoriteActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	FavoriteUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));
	FavoriteUI->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AFurnitureFavoriteActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFurnitureFavoriteActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

