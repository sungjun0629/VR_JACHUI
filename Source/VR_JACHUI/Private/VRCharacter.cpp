// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MoveComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "WidgetPointerComponent.h"
#include "TelepoartDest_BedRoom.h"
#include "TeleportDest_ChairRoom.h"
#include "TeleportDest_DeskRoom.h"
#include <Kismet/GameplayStatics.h>
#include "GrabComponent.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "RoomChoiceWidget.h"
#include "FavoriteCategoryWidget.h"
#include <Components/ArrowComponent.h>
#include "ItemCheckForDetailComponent.h"
#include "RoomTransferActor.h"
#include "RoomLight.h"
#include "GoingMyRoomActor.h"
#include "GoingMyRoomWidget.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "CameraPawn.h"





// Sets default values
AVRCharacter::AVRCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	hmdCam = CreateDefaultSubobject<UCameraComponent>(TEXT("HMD Camera"));
	hmdCam->SetupAttachment(RootComponent);

	hmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"));
	hmdMesh->SetupAttachment(hmdCam);

	leftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Motion Controller"));
	leftMotionController->SetupAttachment(RootComponent);
	leftMotionController->SetTrackingMotionSource(FName("Left"));

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"));
	leftHand->SetupAttachment(leftMotionController);

	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"));
	leftLog->SetupAttachment(leftMotionController);
	leftLog->SetRelativeLocation(FVector(0, 0, 15));
	leftLog->SetRelativeRotation(FRotator(0, 180, 0));
	leftLog->SetWorldSize(10);
	leftLog->SetTextRenderColor(FColor(255, 255, 0, 255));
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);

	rightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Motion Controller"));
	rightMotionController->SetupAttachment(RootComponent);
	rightMotionController->SetTrackingMotionSource(FName("Right"));

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightMotionController);

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightMotionController);
	rightLog->SetWorldSize(10);
	rightLog->SetTextRenderColor(FColor(255, 255, 0, 255));
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);

	rightWidgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"));
	rightWidgetPointer->SetupAttachment(rightHand);
	rightWidgetPointer->SetRelativeRotation(FRotator(0, 90, 0));
	
	RoomChoiceUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("RoomChoiceUI"));
	RoomChoiceUI->SetupAttachment(RootComponent); 
	RoomChoiceUI->SetWidgetClass(URoomChoiceWidget::StaticClass()); 
	RoomChoiceUI->SetRelativeLocation(FVector(0));

	FavoriteUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("FavoriteUI"));
	FavoriteUI->SetupAttachment(RootComponent);
	FavoriteUI->SetWidgetClass(UFavoriteCategoryWidget::StaticClass());
	FavoriteUI->SetRelativeLocation(FVector(35,-95,60));
	FavoriteUI->SetRelativeRotation(FRotator(0,170,0));
	FavoriteUI->SetRelativeScale3D(FVector(0.1f));

	RoomLightUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("RoomLightUI"));
	RoomLightUI->SetupAttachment(RootComponent);
	RoomLightUI->SetWidgetClass(URoomLight::StaticClass());
	RoomLightUI->SetRelativeLocation(FVector(0));

 	//RoomChangeUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("RoomChangeUI"));
 	//RoomChangeUI->SetupAttachment(RootComponent);
 	//RoomChangeUI->SetWidgetClass(UGoingMyRoomWidget::StaticClass());
 	//RoomChangeUI->SetRelativeLocation(FVector(0));

	HouseSpawnSpot = CreateDefaultSubobject<UArrowComponent>(TEXT("HouseSpawnSpot"));
	HouseSpawnSpot->SetRelativeLocation(FVector(300, 0, -60));

	GoingRoomWidgetSpawn = CreateDefaultSubobject<UArrowComponent>(TEXT("WidgetSpawnSpot"));
	GoingRoomWidgetSpawn->SetRelativeLocation(FVector(640, 0, 110));
	GoingRoomWidgetSpawn->SetRelativeRotation(FRotator(0, 180, 0));
	

	itemCheckComp = CreateDefaultSubobject<UItemCheckForDetailComponent>(TEXT("ItemCheck Component"));
	

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	moveComp = CreateDefaultSubobject<UMoveComponent>(TEXT("Move Component"));
	widgetPointerComp = CreateDefaultSubobject<UWidgetPointerComponent>(TEXT("Widget Pointer Component"));
	grabComp = CreateDefaultSubobject<UGrabComponent>(TEXT("Grab Component"));

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 양손 로그 초기화
	leftLog->SetText(FText::FromString("Left Log..."));
	rightLog->SetText(FText::FromString("Right Log..."));

	// 머리 장비 기준점 설정
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	pc = GetController<APlayerController>();

	if (pc != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subSys != nullptr)
		{
			subSys->AddMappingContext(imc_VRmap, 0);
		}
	}

	BedRoom = Cast<ATelepoartDest_BedRoom>(UGameplayStatics::GetActorOfClass(GetWorld(), ATelepoartDest_BedRoom::StaticClass()));
	ChairRoom = Cast<ATeleportDest_ChairRoom>(UGameplayStatics::GetActorOfClass(GetWorld(), ATeleportDest_ChairRoom::StaticClass()));
	DeskRoom = Cast<ATeleportDest_DeskRoom>(UGameplayStatics::GetActorOfClass(GetWorld(), ATeleportDest_DeskRoom::StaticClass()));

	
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent != nullptr)
	{
		moveComp->SetupPlayerInputComponent(enhancedInputComponent, inputActions);
		widgetPointerComp->SetupPlayerInputComponent(enhancedInputComponent, inputActions);
		grabComp->SetupPlayerInputComponent(enhancedInputComponent, inputActions);
		itemCheckComp->SetupPlayerInputComponent(enhancedInputComponent, inputActions);
	}
}

void AVRCharacter::TeleportChairRoom()
{
	if (ChairRoom)
	{
		FVector Loc = ChairRoom->GetActorLocation();
		this->SetActorLocation(Loc);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Here is Not"));
	}

}

void AVRCharacter::TeleportDeskRoom()
{
	if (DeskRoom)
	{
		FVector DeskLoc = DeskRoom->GetActorLocation();
		this->SetActorLocation(DeskLoc);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Here is Not"));
	}

}


void AVRCharacter::SetLoc()
{

	UE_LOG(LogTemp,Warning,TEXT("SetLoc Called"))
	if (pc != nullptr)
	{
		cameraPawn = Cast<ACameraPawn>(pc->GetPawn());
		if (cameraPawn)
		{
			FVector newLoc = cameraPawn->spawnActor->GetActorLocation() + FVector(0,0,100);
			SetActorLocation(newLoc);
			cameraPawn->spawnActor->Destroy();
			cameraPawn->spawnActor = nullptr;
		}
	}
}

void AVRCharacter::TeleportBedRoom()
 {
 	//지정된 위치로 텔레포트할거임
 	if (BedRoom)
 	{
 		FVector TpLoc = BedRoom->GetActorLocation();
 
 		this->SetActorLocation(TpLoc);
 	}
 
 	else
 	{
 		UE_LOG(LogTemp, Warning, TEXT("Here is Not"));
 	}
 
 }

