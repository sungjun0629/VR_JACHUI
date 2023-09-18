// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemCheckForDetailComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "VRCharacter.h"
#include <Kismet/KismetSystemLibrary.h>
#include "FurnitureInformationUI.h"
#include "../FurnitureDetailRequestActor.h"
#include "EngineUtils.h"


// Sets default values for this component's properties
UItemCheckForDetailComponent::UItemCheckForDetailComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemCheckForDetailComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVRCharacter>();
	FurInfoUI = CreateWidget<UFurnitureInformationUI>(GetWorld(), FurniutreInfoUI);

	for (TActorIterator<AFurnitureDetailRequestActor> it(GetWorld()); it; ++it)
	{
		FurDetailRequestActor = *it;
	}
}


// Called every frame
void UItemCheckForDetailComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemCheckForDetailComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[2], ETriggerEvent::Started, this, &UItemCheckForDetailComponent::CheckItem);

}

void UItemCheckForDetailComponent::CheckItem()
{
	// 무언가를 잡고 있지 않을 때, 잡기 위해 실행한다. 
	if (!isHavingObject)
	{
		FVector startLoc = player->rightMotionController->GetComponentLocation();
		FVector endLoc = startLoc + player->rightMotionController->GetForwardVector() * 1000;
		const TArray<AActor*> IgnoreActor;
		FHitResult hitInfo;

		bool isHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), startLoc, endLoc, TraceTypeQuery1, false, IgnoreActor, EDrawDebugTrace::ForDuration, hitInfo, true);

		if (isHit)
		{
			isHavingObject = true;
			hitObject = hitInfo.GetActor();

			if (FurDetailRequestActor != nullptr && FurInfoUI != nullptr)
			{
				FurDetailRequestActor->GETFurnitureInfo(*hitObject->GetActorNameOrLabel());
				FurInfoUI->AddToViewport();
			}
		}
	}
	// 무언가를 잡고 있을 때, 해당 물체를 unclick 한다. 
	else {
		isHavingObject = false;
		// click 중인 Object를 nullptr로 변경해준다. 
		hitObject = nullptr;
		if(FurInfoUI!=nullptr) FurInfoUI->RemoveFromParent();
	}
}
