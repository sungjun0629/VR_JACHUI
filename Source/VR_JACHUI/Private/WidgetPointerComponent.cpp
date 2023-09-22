// Fill out your copyright notice in the Description page of Project Settings.
#include "WidgetPointerComponent.h"
#include "EnhancedInputComponent.h"
#include "VRCharacter.h"
#include "Components/WidgetInteractionComponent.h"

UWidgetPointerComponent::UWidgetPointerComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UWidgetPointerComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVRCharacter>();

}



void UWidgetPointerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UWidgetPointerComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[2], ETriggerEvent::Started, this, &UWidgetPointerComponent::PressButton);
	enhancedInputComponent->BindAction(inputActions[2], ETriggerEvent::Completed, this, &UWidgetPointerComponent::ReleaseButton);
}

void UWidgetPointerComponent::PressButton()
{
	player->rightWidgetPointer->PressPointerKey(EKeys::LeftMouseButton);
	UE_LOG(LogTemp,Warning,TEXT("press"));
}

void UWidgetPointerComponent::ReleaseButton()
{
	player->rightWidgetPointer->ReleasePointerKey(EKeys::LeftMouseButton);
	UE_LOG(LogTemp, Warning, TEXT("release"));
}

