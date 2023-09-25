// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h>
#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include "PlayerSpawnActor.h"
#include "VRCharacter.h"

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
	spawnActor = Cast<APlayerSpawnActor>(UGameplayStatics::GetActorOfClass(GetWorld(), playerSpawnActor));
	player = Cast<AVRCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), VRCharacter));
}


// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector P0 = GetActorLocation();
	FVector vt = Direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P, true);


	//if(havingObject!=nullptr) UE_LOG(LogTemp,Warning,TEXT("%s"), *(havingObject->GetName()));
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
	PlayerInputComponent->BindAction(TEXT("ChangeSpawnLoc"), IE_Pressed,  this, &ACameraPawn::ChangeSpawnLoc);
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
		if(!isRotate)
		{
			havingObject->belayed = true;
			if (havingObject)
			{
				// Drop�Ѵ�. 
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), dustEffect, havingObject->furnitureMesh->GetComponentLocation(), FRotator(0, 1, 180), FVector(15));
				havingObject->furnitureMesh->SetRenderCustomDepth(false);
			}
			havingObject = nullptr;
			isGetFurniture = false;
		}
		else {
			// ���� ȸ�����̶�� Ŭ�� ��, ȸ���� ���ش�. -> UX���� ���(����� ����)
			Rotate();
			havingObject = nullptr;
		}

	}
	else
	{// �ƹ��͵� ������ ���� ���¶�� lineTrace�� ���ؼ� �ٽ� object�� ����ش�. 
		
		if (CatchFurniture() && havingObject)
		{
			havingObject->belayed =false;
			havingObject->furnitureMesh->SetRenderCustomDepth(true);
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
	{// ���� ������ Ŭ���� ���� 

		// ������ ��ġ��Ų��. 
		havingObject->belayed = true;
		

		isRotate =true;

		havingObject->isRotate = havingObject->isRotate ? false : true;
		if(havingObject->isRotate) {
		// Rotate Widget�� �����ִٸ� Ų��.
			havingObject->RotateWidget->SetVisibility(true);
			UE_LOG(LogTemp,Warning,TEXT("visibility True"))
		}
		else {
		// Rotate Widget�� �����ִٸ� ����.
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
		//���� spawnActor�� ���ٸ� ������Ų��.
		spawnActor = GetWorld()->SpawnActor<APlayerSpawnActor>(playerSpawnActor);
		spawnActor->isClicked = true;
	}
}


bool ACameraPawn::CanDrop()
{
	if (havingObject)
	{// ��ü�� ���� �ִٸ�
	 // ��ü�� �ٸ� ��ü�� �浹�ϴ��� Ȯ���� �Ѵ�. 



	}

	return false;
}
