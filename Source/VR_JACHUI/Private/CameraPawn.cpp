// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h>
#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UNiagaraSystem> TempParticle(TEXT("/Script/Niagara.NiagaraSystem'/Game/LSJ/Material/FX_DustRun.FX_DustRun'"));
	if (TempParticle.Succeeded())
	{
		dustEffect = TempParticle.Object;
	}
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}


// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector P0 = GetActorLocation();
	FVector vt = Direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P, true);

	if(havingObject!=nullptr) UE_LOG(LogTemp,Warning,TEXT("%s"), *(havingObject->GetName()));
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ACameraPawn::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ACameraPawn::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Distance"), this, &ACameraPawn::MakeDistance);
	PlayerInputComponent->BindAction(TEXT("DragNDrop"), IE_Pressed,  this, &ACameraPawn::DragNDrop);
	PlayerInputComponent->BindAction(TEXT("Rotate"), IE_Pressed,  this, &ACameraPawn::Rotate);

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
	if (havingObject != nullptr && !isRotate)
	{
		havingObject->belayed = true;
		if(havingObject)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), dustEffect, havingObject->furnitureMesh->GetComponentLocation(), FRotator(0,1,180), FVector(15));
			havingObject->furnitureMesh->SetRenderCustomDepth(false);
		}
		havingObject = nullptr;
		isGetFurniture = false; 

	}
	else
	{// 아무것도 잡히지 않은 상태라면 lineTrace를 통해서 다시 object를 잡아준다. 
		
		if (CatchFurniture() && havingObject)
		{
			havingObject->belayed =false;
			isGetFurniture = true;
			isRotate = false;
			havingObject->furnitureMesh->SetRenderCustomDepth(true);
		}

		// 만약 회전중이라면 클릭 시, 회전을 꺼준다. -> UX적인 요소(사용자 경험)
		if(havingObject!=nullptr && isRotate) Rotate();


	}
	UE_LOG(LogTemp,Warning,TEXT("Drop"));
}

bool ACameraPawn::CatchFurniture()
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

		bool isHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), startLoc, endLoc, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, IgnoreActor, EDrawDebugTrace::None, hitInfo, true);

		if (isHit)
		{
			havingObject = Cast<AMyFurnitureActor>(hitInfo.GetActor());
			if (havingObject)
			{
				return true;
			}
		}

	}

	return false;
}

void ACameraPawn::Rotate()
{
	if (havingObject != nullptr)
	{// 현재 가구가 클릭된 상태 
		isRotate =true;

		// 가구를 위치시킨다. 
		havingObject->belayed = true;


		havingObject->isRotate = havingObject->isRotate ? false : true;
		// Rotate Widget을 꺼져있다면 킨다.
		if(havingObject->isRotate) havingObject->RotateWidget->SetVisibility(true);
		// Rotate Widget을 켜져있다면 끈다.
		else {
			havingObject->RotateWidget->SetVisibility(false);
			havingObject->furnitureMesh->SetRenderCustomDepth(false);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), dustEffect, havingObject->furnitureMesh->GetComponentLocation(), FRotator(0, 1, 180), FVector(15));
		}

	}
}
