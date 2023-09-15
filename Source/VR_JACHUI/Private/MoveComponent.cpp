// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Components/TextRenderComponent.h"
#include "VRCharacter.h" 

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
	//enhancedInputComponent->BindAction(inputActions[4], ETriggerEvent::Started, this, &UMoveComponent::RoomChoiceUIKey);

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


void UMoveComponent::RoomChoiceUIKey(const struct FInputActionValue& value)
{
	// 	bool isOpen = false;
	// 	if (isOpen)
	// 	{
	// 		// uiÄÑ±â
	// 		SetVisibility(ESlateVisibility::Visible);
	// 		isOpen = true;
	// 	}
	// 	else
	// 	{
	// 		// UI²ô±â
	// 		ui¾îµð¼­³ª¿È?->SetVisibility(ESlateVisibility::Collapsed);
	// 		isOpen = false;
	// 	}
}

