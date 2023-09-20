// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	
}


// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector P0 = GetActorLocation();
	FVector vt = Direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P, true);
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ACameraPawn::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ACameraPawn::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Distance"), this, &ACameraPawn::MakeDistance);
	PlayerInputComponent->BindAction(TEXT("DragNDrop"), IE_Pressed,  this, &ACameraPawn::DragNDrop);

}


void ACameraPawn::Horizontal(float value)
{
	Direction.Y = value;
}

void ACameraPawn::Vertical(float value)
{
	Direction.X = value;
}

void ACameraPawn::MakeDistance(float value)
{
	SetActorLocation(GetActorLocation() - (FVector(0,0,value) * distSpeed));
}

void ACameraPawn::DragNDrop()
{
	if (havingObject != nullptr)
	{
		havingObject->belayed = true;
		havingObject = nullptr;
	}
	isGetFurniture = false; 
	UE_LOG(LogTemp,Warning,TEXT("Drop"));
}
