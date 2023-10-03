// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFurnitureActor.h"
#include <Engine/StaticMesh.h>
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "CameraPawn.h"
#include <PhysicsEngine/PhysicsConstraintComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <UMG/Public/Blueprint/WidgetLayoutLibrary.h>

// Sets default values
AMyFurnitureActor::AMyFurnitureActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));
	PhysicsConstraint->SetupAttachment(RootComponent);

	RotateWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Rotate Widget"));
	RotateWidget->SetupAttachment(furnitureMesh);

}

// Called when the game starts or when spawned
void AMyFurnitureActor::BeginPlay()
{
	Super::BeginPlay();
	
	pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//CameraPawn = Cast<ACameraPawn>(GetOwner());

	CameraPawn = Cast<ACameraPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), CameraPawnClass));
	if(CameraPawn) 
	{
		CameraPawn->isGetFurniture = true;
		CameraPawn->havingObject = this;
	}
}

// Called every frame
void AMyFurnitureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//setFurnitureLoc();
	if(CameraPawn && CameraPawn->isGetFurniture && !belayed) 
	//if(CameraPawn)
	{
		setFurnitureLoc();
	}
	
	//if(isRotate) RotateFurniture();

}

void AMyFurnitureActor::changeAsset()
{
	UStaticMesh* newStaticMesh = LoadObject<UStaticMesh>(nullptr, *assetDir);
	if (newStaticMesh)
	{
		furnitureMesh->SetStaticMesh(newStaticMesh);
	}
}

void AMyFurnitureActor::setFurnitureLoc()
{
	FVector2D MouseScreenPostion;
	FVector MouseWorldLocation, MouserWorldDirection;

	if (pc)
	{
		//pc->GetMousePosition(MouseScreenPostion.X, MouseScreenPostion.Y);
	/*	pc->DeprojectScreenPositionToWorld(MouseScreenPostion.X , MouseScreenPostion.Y, MouseWorldLocation, MouserWorldDirection);*/
		//pc->DeprojectMousePositionToWorld(MouseWorldLocation, MouserWorldDirection);
		MouseWorldLocation = CameraPawn->rightHand->GetComponentLocation();
		MouserWorldDirection = CameraPawn ->rightHand->GetRightVector();


		FVector startLoc = MouseWorldLocation;
		FVector endLoc = MouseWorldLocation + MouserWorldDirection * 10000;
		const TArray<AActor*> IgnoreActor; 
		FHitResult hitInfo;

		bool isHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), startLoc, endLoc, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel3), false, IgnoreActor, EDrawDebugTrace::None, hitInfo, true);


		if (isHit)
		{
			SetActorLocation(hitInfo.Location * FVector(1,1,0));
		}
	}


}

void AMyFurnitureActor::RotateFurniture()
{
	//float mouseX, mouseY;
	////UGameplayStatics::GetPlayerController(GetWorld(),0)->GetMousePosition(mouseX, mouseY);
	//mouseX = CameraPawn->hitInfo.Location.X; mouseY = CameraPawn->hitInfo.Location.Y;
	//FVector2D viewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld())/2;
	//FVector Start = UKismetMathLibrary::MakeVector(mouseX, mouseY, 0);
	//FVector End = UKismetMathLibrary::MakeVector(viewportSize.X, viewportSize.Y, 0);
	//
	//FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
	//furnitureMesh->SetWorldRotation(newRotation);

	//FVector baseVector = CameraPawn->rightMotionController->GetRightVector();
	//FVector handlingVector = (CameraPawn->rightMotionController->GetComponentLocation() - baseVector).GetSafeNormal();

	//float cosRad = FVector::DotProduct(baseVector, handlingVector);
	//float angle = FMath::RadiansToDegrees(FMath::Acos(cosRad));

	//FVector result = FVector::CrossProduct(baseVector, handlingVector);
	//float dirValue = 1;

	//if (FVector::DotProduct(result, CameraPawn->rightMotionController->GetForwardVector()) >= 0)
	//{
	//	//bIsLeft = true;
	//	dirValue = -1;
	//}
	//else
	//{
	//	//bIsLeft = false;
	//	dirValue = 1;
	//}

	//FRotator newRot = GetActorRotation() + FRotator(0, angle* 0.01 * dirValue, 0);
	//furnitureMesh->SetWorldRotation(FMath::Lerp(GetActorRotation(), newRot, 0.7f));

}

