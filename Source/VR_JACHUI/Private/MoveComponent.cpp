// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Components/TextRenderComponent.h"
#include "VRCharacter.h" 
#include <UMG/Public/Components/WidgetComponent.h>
#include <Components/ArrowComponent.h>
#include "RoomTransferActor.h"
#include <Kismet/GameplayStatics.h>
#include "MyFurnitureActor.h"
#include "GoingMyRoomActor.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVRCharacter>();
	furniture = Cast<AMyFurnitureActor>(UGameplayStatics::GetActorOfClass(GetWorld(),AMyFurnitureActor::StaticClass()));
	house = Cast<ARoomTransferActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ARoomTransferActor::StaticClass()));
	goingroom = Cast<AGoingMyRoomActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGoingMyRoomActor::StaticClass()));
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[0], ETriggerEvent::Triggered, this, &UMoveComponent::Move);
	enhancedInputComponent->BindAction(inputActions[0], ETriggerEvent::Completed, this, &UMoveComponent::Move);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Triggered, this, &UMoveComponent::Rotate);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Completed, this, &UMoveComponent::Rotate);
	enhancedInputComponent->BindAction(inputActions[4], ETriggerEvent::Started, this, &UMoveComponent::RoomChoiceUIKey);
	enhancedInputComponent->BindAction(inputActions[5], ETriggerEvent::Started, this, &UMoveComponent::FavoriteUIKey);
	enhancedInputComponent->BindAction(inputActions[6], ETriggerEvent::Started, this, &UMoveComponent::GoingInteriorSpawn);
	enhancedInputComponent->BindAction(inputActions[8], ETriggerEvent::Started, this, &UMoveComponent::RoomLightUIKey);

}

void UMoveComponent::Move(const FInputActionValue& value)
{
	if(player->moveMode)
	{
			FVector2D controllerInput = value.Get<FVector2D>();

			FVector forwardVec = FRotationMatrix(player->pc->GetControlRotation()).GetUnitAxis(EAxis::X);
			FVector rightVec = FRotationMatrix(player->pc->GetControlRotation()).GetUnitAxis(EAxis::Y);

			player->AddMovementInput(forwardVec, controllerInput.X);
			player->AddMovementInput(rightVec, controllerInput.Y);
	}
}

void UMoveComponent::Rotate(const FInputActionValue& value)
{
	if(player->moveMode)
	{
		FVector2D rightConInput = value.Get<FVector2D>();
			if (player->pc != nullptr)
			{
				player->pc->AddYawInput(rightConInput.X);
				player->pc->AddPitchInput(rightConInput.Y);
			}
	}
}

//roomchoice ui 온오프 함수
void UMoveComponent::RoomChoiceUIKey(const FInputActionValue& value)
{
	bool isRUIVisible = player->RoomChoiceUI->IsVisible();

	player->RoomChoiceUI->SetVisibility(!isRUIVisible);
}

//favorite ui 온오프 함수
void UMoveComponent::FavoriteUIKey(const struct FInputActionValue& value)
{
	bool isFUIVisible = player->FavoriteUI->IsVisible();

	player->FavoriteUI->SetVisibility(!isFUIVisible);
}

//RoomLight ui 온오프 함수
void UMoveComponent::RoomLightUIKey(const struct FInputActionValue& value)
{
	bool isLUIVisible = player->RoomLightUI->IsVisible();

	player->RoomLightUI->SetVisibility(!isLUIVisible);
}


void UMoveComponent::GoingInteriorSpawn(const struct FInputActionValue& value)
{
	//키 누른거에 바인딩 하기
	UWorld* World = GetWorld();
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector spawnPoint1 = player->GetTransform().TransformPosition(player->HouseSpawnSpot->GetComponentLocation());
	FVector spawnPoint2 = player->GetTransform().TransformPosition(player->GoingRoomWidgetSpawn->GetComponentLocation());

	if(!alreadySpawn)
	{
		house = World->SpawnActor<ARoomTransferActor>(room, spawnPoint1, FRotator::ZeroRotator, Param);
		goingroom = World->SpawnActor<AGoingMyRoomActor>(GoingWidget, spawnPoint2, FRotator::ZeroRotator, Param);
		alreadySpawn = true;
	}

	else
	{
		if (house)
		{
			house->Destroy();
			house = nullptr; // 포인터 초기화
		}
		if (goingroom)
		{
			goingroom->Destroy();
			goingroom = nullptr; // 포인터 초기화
		}

		// 새로운 액터가 다음에 함수를 호출할 때 스폰될 수 있도록 alreadySpawn을 다시 false로 설정
		alreadySpawn = false;
	}
}

