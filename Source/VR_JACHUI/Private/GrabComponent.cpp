// Fill out your copyright notice in the Description page of Project Settings.

#include "GrabComponent.h"
#include "VRCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "MotionControllerComponent.h"
#include "TestPickUp.h"
#include "Components/TextRenderComponent.h"


UGrabComponent::UGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}



void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVRCharacter>();

}


void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UGrabComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[3], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
}

void UGrabComponent::GrabObject()
{
	// 1. 라인트레이스 이용시
	FHitResult hitInfo;
	FVector startLoc = player->rightMotionController->GetComponentLocation();
	FVector endLoc = startLoc + player->rightMotionController->GetUpVector() * -50.0f;

	if (GetWorld()->LineTraceSingleByProfile(hitInfo, startLoc, endLoc, FName("PickUp")))
	{
		ATestPickUp* pickObject = Cast<ATestPickUp>(hitInfo.GetActor());
		if (pickObject != nullptr)
		{
			pickObject->Grabbed(player->rightHand);
		}

		player->rightLog->SetText(FText::FromString(FString::Printf(TEXT("Grab object: %s"), *hitInfo.GetActor()->GetName())));
		UE_LOG(LogTemp, Warning, TEXT("Grab object: %s"), *hitInfo.GetActor()->GetName());
	}
	else
	{
		player->rightLog->SetText(FText::FromString(FString::Printf(TEXT("No Hit"))));
		UE_LOG(LogTemp, Warning, TEXT("No Hit"));
	}
}

void UGrabComponent::ReleaseObject()
{

}

void UGrabComponent::RightHandMove(const struct FInputActionValue& value)
{

}

