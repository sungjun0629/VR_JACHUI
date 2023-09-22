// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpawnActor.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
APlayerSpawnActor::APlayerSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSpawnActor::BeginPlay()
{
	Super::BeginPlay();

	pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
}

// Called every frame
void APlayerSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isClicked)
	{
		SetLoc();
	}
}

void APlayerSpawnActor::SetLoc()
{
	FVector2D MouseScreenPostion;
	FVector MouseWorldLocation, MouserWorldDirection;

	if (pc)
	{
		pc->DeprojectMousePositionToWorld(MouseWorldLocation, MouserWorldDirection);

		FVector startLoc = MouseWorldLocation;
		FVector endLoc = MouseWorldLocation + MouserWorldDirection * 10000;
		const TArray<AActor*> IgnoreActor;
		FHitResult hitInfo;

		bool isHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), startLoc, endLoc, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel3), false, IgnoreActor, EDrawDebugTrace::None, hitInfo, true);

		if (isHit)
		{
			SetActorLocation(hitInfo.Location * FVector(1, 1, 0));
		}
	}

}

