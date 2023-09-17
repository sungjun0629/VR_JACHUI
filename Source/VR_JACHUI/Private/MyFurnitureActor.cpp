// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFurnitureActor.h"
#include <Engine/StaticMesh.h>
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
AMyFurnitureActor::AMyFurnitureActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	//RootComponent = boxComp;


	furnitureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("furnitureMesh"));
	furnitureMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	furnitureMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempObject(*assetDir);
	if (TempObject.Succeeded())
	{
		furnitureMesh->SetStaticMesh(TempObject.Object);
	}


}

// Called when the game starts or when spawned
void AMyFurnitureActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyFurnitureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyFurnitureActor::changeAsset()
{
	UStaticMesh* newStaticMesh =  LoadObject<UStaticMesh>(nullptr, *assetDir);
	if (newStaticMesh)
	{
		furnitureMesh->SetStaticMesh(newStaticMesh);
	}
}

