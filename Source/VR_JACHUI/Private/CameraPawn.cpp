// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h>
#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include "PlayerSpawnActor.h"
#include "VRCharacter.h"
#include <HeadMountedDisplay/Public/MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include <Engine/Engine.h>

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

	ColliComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = ColliComp;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(RootComponent);

	rightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Motion Controller"));
	rightMotionController->SetupAttachment(RootComponent);
	rightMotionController->SetTrackingMotionSource(FName("Right"));
	rightMotionController->SetRelativeLocation(FVector(50,30,-50));
	

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightMotionController);
	rightHand->SetRelativeLocation(FVector(20, 0, 40));
	rightHand->SetRelativeRotation(FRotator(180, 90, 90));

	rightWidgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"));
	rightWidgetPointer->SetupAttachment(rightHand);
	rightWidgetPointer->SetRelativeRotation(FRotator(0, 90, 0));

	FavoriteUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("FavoriteUI"));
	FavoriteUI->SetupAttachment(RootComponent);
	FavoriteUI->SetWidgetClass(UFavoriteCategoryWidget::StaticClass());
	FavoriteUI->SetRelativeLocation(FVector(35, -95, 60));
	FavoriteUI->SetRelativeRotation(FRotator(0, 170, 0));
	FavoriteUI->SetRelativeScale3D(FVector(0.1f));

}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	spawnActor = Cast<APlayerSpawnActor>(UGameplayStatics::GetActorOfClass(GetWorld(), playerSpawnActor));
	player = Cast<AVRCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), VRCharacter));
	RoomGM = GetWorld()->GetAuthGameMode<AMyRoomGameModeBase>();
}


// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector P0 = GetActorLocation();
	FVector vt = Direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P, true);

	DebugLine();
	//if(havingObject!=nullptr) UE_LOG(LogTemp,Warning,TEXT("%s"), *(havingObject->GetName()));
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ACameraPawn::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ACameraPawn::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Distance"), this, &ACameraPawn::MakeDistance);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &ACameraPawn::MakeRotate);
	PlayerInputComponent->BindAction(TEXT("DragNDrop"), IE_Pressed,  this, &ACameraPawn::DragNDrop);
	PlayerInputComponent->BindAction(TEXT("Rotate"), IE_Pressed,  this, &ACameraPawn::Rotate);
	PlayerInputComponent->BindAction(TEXT("ChangeSpawnLoc"), IE_Pressed,  this, &ACameraPawn::ChangeSpawnLoc);
	PlayerInputComponent->BindAction(TEXT("Click"), IE_Pressed,  this, &ACameraPawn::ClickButton);
	PlayerInputComponent->BindAction(TEXT("SpeedUP"), IE_Pressed,  this, &ACameraPawn::SpeedUP);
	PlayerInputComponent->BindAction(TEXT("SpeedDown"), IE_Pressed,  this, &ACameraPawn::SpeedDOWN);
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
	if(!havingObject)
	SetActorLocation(GetActorLocation() - (FVector(0,0,value) * distSpeed));
}

void ACameraPawn::MakeRotate(float value)
{
	if(havingObject)
	{
		FRotator newRot = havingObject->GetActorRotation() + FRotator(0, value * rotSpeed , 0);
		havingObject->furnitureMesh->SetWorldRotation(FMath::Lerp(havingObject->GetActorRotation(), newRot, 0.7f));
	}
}

void ACameraPawn::DragNDrop()
{
	if (havingObject != nullptr)
	{
		if(!isRotate)
		{
			havingObject->belayed = true;
			
			// Drop한다. 
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), dustEffect, havingObject->furnitureMesh->GetComponentLocation()+ FVector(0,0,10), FRotator(0, 0, 0), FVector(15));
			havingObject->furnitureMesh->SetRenderCustomDepth(false);
			havingObject->RotateWidget->SetVisibility(false);
			havingObject->isRotate = false;
			// 현재 위치를 저장해준다.
			RoomGM->SaveData(havingObject->GetName(), havingObject->GetActorLocation(), havingObject->GetActorRotation());


			havingObject = nullptr;
			isGetFurniture = false;
		}
		else {
			// 만약 회전중이라면 클릭 시, 회전을 꺼준다. -> UX적인 요소(사용자 경험)
			Rotate();
			havingObject = nullptr;
		}

	}
	else
	{// 아무것도 잡히지 않은 상태라면 lineTrace를 통해서 다시 object를 잡아준다. 
		
		if (CatchFurniture() && havingObject)
		{
			havingObject->belayed =false;
			havingObject->furnitureMesh->SetRenderCustomDepth(true);
			havingObject->RotateWidget->SetVisibility(false);
			havingObject->isRotate = false;
		}

		isGetFurniture = true;
		isRotate = false;

	
	}
	UE_LOG(LogTemp,Warning,TEXT("Drop"));
}

bool ACameraPawn::CatchFurniture()
{
	FVector2D MouseScreenPostion;
	FVector MouseWorldLocation, MouserWorldDirection;

	if (pc)
	{
		//pc->DeprojectMousePositionToWorld(MouseWorldLocation, MouserWorldDirection);
		MouseWorldLocation = rightHand->GetComponentLocation();
		MouserWorldDirection = rightHand->GetRightVector();

		FVector startLoc = MouseWorldLocation;
		FVector endLoc = MouseWorldLocation + MouserWorldDirection * 10000;
		const TArray<AActor*> IgnoreActor;
		FHitResult hitInfo2;

		bool isHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), startLoc, endLoc, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, IgnoreActor, EDrawDebugTrace::None, hitInfo2, true);

		if (isHit)
		{
			havingObject = Cast<AMyFurnitureActor>(hitInfo2.GetActor());
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

		// 가구를 위치시킨다. 
		havingObject->belayed = true;
		

		isRotate =true;

		havingObject->isRotate = havingObject->isRotate ? false : true;
		if(havingObject->isRotate) {
		// Rotate Widget을 꺼져있다면 킨다.
			havingObject->RotateWidget->SetVisibility(true);
			UE_LOG(LogTemp,Warning,TEXT("visibility True"))
		}
		else {
		// Rotate Widget을 켜져있다면 끈다.
			havingObject->RotateWidget->SetVisibility(false);
			havingObject->furnitureMesh->SetRenderCustomDepth(false);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), dustEffect, havingObject->furnitureMesh->GetComponentLocation(), FRotator(0, 1, 180), FVector(15));
			UE_LOG(LogTemp,Warning,TEXT("visibility False"))

		}

	}
}

void ACameraPawn::ChangeSpawnLoc()
{
	if (spawnActor)
	{
		spawnActor->isClicked = spawnActor->isClicked ? false : true ;
		UE_LOG(LogTemp,Warning,TEXT("change Spawn Loc"))
		if(player && spawnActor->isClicked == false) {
			UE_LOG(LogTemp,Warning,TEXT("set player loc"))	
			player->SetLoc();
		}
	}
	else {
		UE_LOG(LogTemp,Warning,TEXT("change Spawn Loc but no SpawnActor"))
		//만약 spawnActor가 없다면 스폰시킨다.
		spawnActor = GetWorld()->SpawnActor<APlayerSpawnActor>(playerSpawnActor);
		spawnActor->isClicked = true;
	}
}


bool ACameraPawn::CanDrop()
{
	if (havingObject)
	{// 물체를 갖고 있다면
	 // 물체와 다른 물체가 충돌하는지 확인을 한다. 



	}

	return false;
}

void ACameraPawn::ClickButton()
{
	rightWidgetPointer->PressPointerKey(EKeys::LeftMouseButton);
	UE_LOG(LogTemp,Warning,TEXT("ClickButton")); 
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "ClickButton");
	}*/
	/*FPlatformProcess::Sleep(0.2);
	rightWidgetPointer->ReleasePointerKey(EKeys::LeftMouseButton);*/
}

void ACameraPawn::DebugLine()
{
	
	FVector2D MouseScreenPostion;
	FVector MouseWorldLocation, MouserWorldDirection;

	MouseWorldLocation = rightHand->GetComponentLocation();
	MouserWorldDirection = rightHand->GetRightVector();

	FVector startLoc = MouseWorldLocation;
	FVector endLoc = MouseWorldLocation + MouserWorldDirection * 10000;
	const TArray<AActor*> IgnoreActor;

	DrawDebugLine(GetWorld(), startLoc, endLoc , FColor::Red);

	bool isHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), startLoc, endLoc, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, IgnoreActor, EDrawDebugTrace::None, hitInfo, true);
}

void ACameraPawn::SpeedDOWN()
{
	rotSpeed -= 0.1f;
}

void ACameraPawn::SpeedUP()
{
	rotSpeed += 0.1f;
}
