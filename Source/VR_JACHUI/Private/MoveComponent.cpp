// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Components/TextRenderComponent.h"
#include "VRCharacter.h" 
#include <UMG/Public/Components/WidgetComponent.h>
#include <Components/ArrowComponent.h>
#include "RoomTransferActor.h"

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

}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	FString str = FString::Printf(TEXT("SetupPlayerInputComponent"));
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, str);
	enhancedInputComponent->BindAction(inputActions[0], ETriggerEvent::Triggered, this, &UMoveComponent::Move);
	enhancedInputComponent->BindAction(inputActions[0], ETriggerEvent::Completed, this, &UMoveComponent::Move);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Triggered, this, &UMoveComponent::Rotate);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Completed, this, &UMoveComponent::Rotate);
	enhancedInputComponent->BindAction(inputActions[4], ETriggerEvent::Started, this, &UMoveComponent::RoomChoiceUIKey);
	enhancedInputComponent->BindAction(inputActions[5], ETriggerEvent::Started, this, &UMoveComponent::FavoriteUIKey);
	enhancedInputComponent->BindAction(inputActions[6], ETriggerEvent::Started, this, &UMoveComponent::GoingInteriorSpawn);

}

void UMoveComponent::Move(const FInputActionValue& value)
{
	FVector2D controllerInput = value.Get<FVector2D>();

	FString str = FString::Printf(TEXT("x : %.2f, y : %.2f"), controllerInput.X, controllerInput.Y);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, str);

	FVector forwardVec = FRotationMatrix(player->pc->GetControlRotation()).GetUnitAxis(EAxis::X);
	FVector rightVec = FRotationMatrix(player->pc->GetControlRotation()).GetUnitAxis(EAxis::Y);

	player->AddMovementInput(forwardVec, controllerInput.X);
	player->AddMovementInput(rightVec, controllerInput.Y);
}

void UMoveComponent::Rotate(const FInputActionValue& value)
{
	FVector2D rightConInput = value.Get<FVector2D>();

	if (player->pc != nullptr)
	{
		player->pc->AddYawInput(rightConInput.X);
		player->pc->AddPitchInput(rightConInput.Y);
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

//void UMoveComponent::RoomChangeUIKey(const struct FInputActionValue& value)
//{
//	bool isRCUIVisible = player->RoomChangeUI->IsVisible();
//
//	player->RoomChangeUI->SetVisibility(!isRCUIVisible);
//	//player->
//}

void UMoveComponent::GoingInteriorSpawn(const struct FInputActionValue& value)
{
	//키 누른거에 바인딩 하기
	UWorld* World = GetWorld();
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector spawnPoint1 = player->GetTransform().TransformPosition(player->HouseSpawnSpot->GetComponentLocation());
	FVector spawnPoint2 = player->GetTransform().TransformPosition(player->GoingRoomWidgetSpawn->GetComponentLocation());

	ARoomTransferActor* house = World->SpawnActor<ARoomTransferActor>(room,spawnPoint1, FRotator::ZeroRotator, Param);
	AGoingMyRoomActor* goingroom = World->SpawnActor<AGoingMyRoomActor>(GoingWidget, spawnPoint2, FRotator::ZeroRotator, Param);
}

