// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomTransferActor.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/RotatingMovementComponent.h>

// Sets default values
ARoomTransferActor::ARoomTransferActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Root->SetBoxExtent(FVector(260,260,100));
	Walls = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Walls"));
	Walls->SetupAttachment(Root);
	Walls->SetWorldScale3D(FVector(0.5f));
	Walls->SetWorldLocation(FVector(160,50,0));

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/ArchVizInteriorVol3/Meshes/SM_Room_Walls.SM_Room_Walls'"));
	if (TempMesh.Succeeded())
	{
		Walls->SetStaticMesh(TempMesh.Object);
	}

	floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floors"));
	floor->SetupAttachment(Root);
	floor->SetWorldScale3D(FVector(0.5f));
	floor->SetWorldLocation(FVector(160, 50, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempSecond(TEXT("/Script/Engine.StaticMesh'/Game/ArchVizInteriorVol3/Meshes/SM_Floor.SM_Floor'"));
	if (TempSecond.Succeeded())
	{
		floor->SetStaticMesh(TempSecond.Object);
	}

	RotateMove = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotateMove"));
}

// Called when the game starts or when spawned
void ARoomTransferActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomTransferActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

