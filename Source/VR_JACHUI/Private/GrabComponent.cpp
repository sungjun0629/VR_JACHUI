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
#include <Kismet/KismetSystemLibrary.h>


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

	//RightHandMove();
}

void UGrabComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[3], ETriggerEvent::Started, this, &UGrabComponent::TargetingFurniture);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Triggered, this, &UGrabComponent::MoveObjectForward);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Triggered, this, &UGrabComponent::MoveObjectBackward);

}

void UGrabComponent::GetOrDeleteObject()
{
	//if (!isHavingObject)
	//{
	//	FVector startLoc = player->hmdCam->GetComponentLocation();
	//	FVector endLoc = startLoc + player->hmdCam->GetForwardVector() * 1000;
	//	const TArray<AActor*> IgnoreActor;
	//	FHitResult hitInfo;
	//
	//	bool isHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), startLoc, endLoc, TraceTypeQuery1, false, IgnoreActor, EDrawDebugTrace::ForDuration, hitInfo, true);
	//
	//	if (isHit)
	//	{
	//		isHavingObject = true;
	//		hitObject = hitInfo.GetActor();
	//		UE_LOG(LogTemp, Warning, TEXT("%s"), *hitObject->GetActorNameOrLabel());
	//	}
	//}
	//// 무언가를 잡고 있을 때, 해당 물체를 unclick 한다. 
	//else 
	//{
	//	isHavingObject = false;
	//	// click 중인 Object를 nullptr로 변경해준다. 
	//	hitObject = nullptr;
	//}
}

void UGrabComponent::TargetingFurniture()
{
	//라인트레이스를 쏜다
	FVector startLoc = player->hmdCam->GetComponentLocation();
	FVector endLoc = startLoc + player->hmdCam->GetForwardVector() * 1000;
	FHitResult hitInfo;
	const TArray<AActor*> IgnoreActor;
	FCollisionQueryParams param;
	param.AddIgnoredActor(GetOwner());
	int HitCount = 0;

	//라인을 두번 맞으면 furniture의 movable이 false가 된다.
	//movable이 true면
	//MoveObject를 활성화하고
	//movable이 false면
	//원상복귀한다.

	//맞은 액터가 FurnitureActor인지 확인한다.
	//FurnitureActor가 맞았다면
	//bool isHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), startLoc, endLoc, TraceTypeQuery1, false, IgnoreActor, EDrawDebugTrace::ForDuration, hitInfo ,true);
	bool isHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility, param);
	DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, true, 2.0f, 0, 2.0f);


	if (isHit)
	{


		AMyFurnitureActor* furniture = Cast<AMyFurnitureActor>(hitInfo.GetActor());
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%s"), *hitInfo.GetActor()->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *hitInfo.GetActor()->GetName());
		if (furniture)
		{

			//FurnitureActor의 스태틱메쉬에 있는 RenderCustomDepth를 true로 바꾼다.
			if (!furniture->movable)
			{
				//라인을 한번 맞으면 furniture의 movable을 true로 바꾸고
				furniture->furnitureMesh->SetRenderCustomDepth(true);
				furniture->movable = true;
				HitCount++;
			}
		}
		else if (HitCount == 2)
		{
			furniture->furnitureMesh->SetRenderCustomDepth(false);
			furniture->movable = false;
			HitCount = 0;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hit"));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString("No Hit"));
	}
}

void UGrabComponent::MoveObjectForward(const struct FInputActionValue& value)
{
	//if ()
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Forward"));
	//	hitObject->AddActorWorldOffset(player->GetActorForwardVector() * 30);
	//}
}

void UGrabComponent::MoveObjectBackward(const struct FInputActionValue& value)
{
	//if (hitObject)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("backward"));
	//	hitObject->AddActorWorldOffset(player->GetActorForwardVector() * -30);
	//}
}

//void UGrabComponent::GrabObject()
//{
//	//if (grabbedObject != nullptr)
//	//{
//	//	return;
//	//}	
//	//// 3. Overlap 방식을 사용할 때
//	//TArray<FOverlapResult> hitInfos;
//	//FVector startLoc = player->rightHand->GetComponentLocation();
//	//
//	//if (GetWorld()->OverlapMultiByProfile(hitInfos, startLoc, FQuat::Identity, FName("PickUp"), FCollisionShape::MakeSphere(20)))
//	//{
//	//	for (const FOverlapResult& hitInfo : hitInfos)
//	//	{
//	//		if (ATestPickUp* pickObj = Cast<ATestPickUp>(hitInfo.GetActor()))
//	//		{
//	//			pickObj->Grabbed(player->rightHand);
//	//			grabbedObject = pickObj;
//	//
//	//			player->pc->PlayHapticEffect(grab_Haptic, EControllerHand::Right, 1.0f, false);
//	//			break;
//	//		}
//	//	}
//	//}
//	
//	if (!IsGrab)
//	{
//		FVector startLoc = player->hmdCam->GetComponentLocation();
//		FVector endLoc = startLoc + player->hmdCam->GetForwardVector()*500.f;
//		FHitResult hitInfo;
//		FCollisionQueryParams params;
//		params.AddIgnoredActor(player);
//		DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Green, false, 1.0f);
//		if (GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility, params))
//		{
//			if (AMyFurnitureActor* hitActor = Cast<AMyFurnitureActor>(hitInfo.GetActor()))
//			{
//				UPrimitiveComponent* hitComponent = Cast<UPrimitiveComponent>(hitActor->GetRootComponent());
//				player->PhysicsHandle->GrabComponentAtLocationWithRotation(hitComponent,NAME_None,hitActor->GetActorLocation(), hitActor->GetActorRotation());
//				IsGrab = true;
//			}
//		}
//	}
//	//라인트레이스를 사용한다.
//	//손에서 부터 나가는 라인트레이스에
//	//가구가 닿게 되면 잡는다.
//	//Physicshandle컴포넌트를 캐릭터에 추가한다.
//	//physicshandle->grab component at location with rotation
//	//isgrab? bool값을 추가한다.
//	//release가 됐을때 bool값이 true라면
//	//physics handle에서 releaseComponent를 추가하고 grab object를 false로 바꾼다.
//}
//
//void UGrabComponent::ReleaseObject()
//{
//	//if (grabbedObject != nullptr)
//	//{
//	//	// 물체를 손에서 분리하고, 물리 능력을 활성화한다.
//	//	grabbedObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//	//	grabbedObject->boxcomp->SetSimulatePhysics(true);
//	//
//	//	// 물체의 던지는 방향에 따른 힘(선형, 회전력)을 가한다.
//// 	//	if (!deltaLoc.IsNearlyZero())
//// 	//	{
//// 	//		grabbedObject->boxcomp->AddImpulse(deltaLoc.GetSafeNormal() * throwPower);
//// 	//		grabbedObject->boxcomp->AddTorqueInRadians(deltaRot.GetRotationAxis() * rotSpeed);
//// 	//	}
//	//
//	//	grabbedObject = nullptr;
//	//}
//	if (IsGrab)
//	{
//		player->PhysicsHandle->ReleaseComponent();
//	}
//}
//
//void UGrabComponent::RightHandMove()
//{
//	//FVector direction = value.Get<FVector>();
//	//player->rightMotionController->SetRelativeLocation(player->rightMotionController->GetRelativeLocation() + direction.GetSafeNormal());
//
//	FVector startLoc = player->hmdCam->GetComponentLocation();
//	FVector endLoc = startLoc + player->hmdCam->GetForwardVector() * 500.f;
//	FVector NewLocation = startLoc +endLoc;
//		if (IsGrab)
//		{
//			player->PhysicsHandle->SetTargetLocation(NewLocation);
//		}
//
//}

