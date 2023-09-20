// Fill out your copyright notice in the Description page of Project Settings.

#include "GrabComponent.h"
#include "VRCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "MotionControllerComponent.h"
#include "TestPickUp.h"
#include "Components/TextRenderComponent.h"
#include <Components/BoxComponent.h>
#include "MyFurnitureActor.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "Camera/CameraComponent.h"


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

	//if (grabbedObject != nullptr)
	//{
	//	deltaLoc = player->rightMotionController->GetComponentLocation() - prevLoc;
	//	prevLoc = player->rightMotionController->GetComponentLocation();
	//
	//	deltaRot = player->rightMotionController->GetComponentQuat() - prevRot.Inverse();
	//	prevRot = player->rightMotionController->GetComponentQuat();
	//}

	RightHandMove();
}

void UGrabComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[3], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
	enhancedInputComponent->BindAction(inputActions[3], ETriggerEvent::Completed, this, &UGrabComponent::ReleaseObject);
}

void UGrabComponent::GrabObject()
{
	//if (grabbedObject != nullptr)
	//{
	//	return;
	//}	
	//// 3. Overlap 방식을 사용할 때
	//TArray<FOverlapResult> hitInfos;
	//FVector startLoc = player->rightHand->GetComponentLocation();
	//
	//if (GetWorld()->OverlapMultiByProfile(hitInfos, startLoc, FQuat::Identity, FName("PickUp"), FCollisionShape::MakeSphere(20)))
	//{
	//	for (const FOverlapResult& hitInfo : hitInfos)
	//	{
	//		if (ATestPickUp* pickObj = Cast<ATestPickUp>(hitInfo.GetActor()))
	//		{
	//			pickObj->Grabbed(player->rightHand);
	//			grabbedObject = pickObj;
	//
	//			player->pc->PlayHapticEffect(grab_Haptic, EControllerHand::Right, 1.0f, false);
	//			break;
	//		}
	//	}
	//}
	
	if (!IsGrab)
	{
		FVector startLoc = player->hmdCam->GetComponentLocation();
		FVector endLoc = startLoc + player->hmdCam->GetForwardVector()*500.f;
		FHitResult hitInfo;
		FCollisionQueryParams params;
		params.AddIgnoredActor(player);
		DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Green, false, 1.0f);
		if (GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility, params))
		{
			if (AMyFurnitureActor* hitActor = Cast<AMyFurnitureActor>(hitInfo.GetActor()))
			{
				UPrimitiveComponent* hitComponent = Cast<UPrimitiveComponent>(hitActor->GetRootComponent());
				player->PhysicsHandle->GrabComponentAtLocationWithRotation(hitComponent,NAME_None,hitActor->GetActorLocation(), hitActor->GetActorRotation());
				IsGrab = true;
			}
		}
	}
	//라인트레이스를 사용한다.
	//손에서 부터 나가는 라인트레이스에
	//가구가 닿게 되면 잡는다.
	//Physicshandle컴포넌트를 캐릭터에 추가한다.
	//physicshandle->grab component at location with rotation
	//isgrab? bool값을 추가한다.
	//release가 됐을때 bool값이 true라면
	//physics handle에서 releaseComponent를 추가하고 grab object를 false로 바꾼다.
}

void UGrabComponent::ReleaseObject()
{
	//if (grabbedObject != nullptr)
	//{
	//	// 물체를 손에서 분리하고, 물리 능력을 활성화한다.
	//	grabbedObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//	grabbedObject->boxcomp->SetSimulatePhysics(true);
	//
	//	// 물체의 던지는 방향에 따른 힘(선형, 회전력)을 가한다.
// 	//	if (!deltaLoc.IsNearlyZero())
// 	//	{
// 	//		grabbedObject->boxcomp->AddImpulse(deltaLoc.GetSafeNormal() * throwPower);
// 	//		grabbedObject->boxcomp->AddTorqueInRadians(deltaRot.GetRotationAxis() * rotSpeed);
// 	//	}
	//
	//	grabbedObject = nullptr;
	//}
	if (IsGrab)
	{
		player->PhysicsHandle->ReleaseComponent();
	}
}

void UGrabComponent::RightHandMove()
{
	//FVector direction = value.Get<FVector>();
	//player->rightMotionController->SetRelativeLocation(player->rightMotionController->GetRelativeLocation() + direction.GetSafeNormal());

	FVector startLoc = player->hmdCam->GetComponentLocation();
	FVector endLoc = startLoc + player->hmdCam->GetForwardVector() * 500.f;
	FVector NewLocation = startLoc +endLoc;
		if (IsGrab)
		{
			player->PhysicsHandle->SetTargetLocation(NewLocation);
		}

}

