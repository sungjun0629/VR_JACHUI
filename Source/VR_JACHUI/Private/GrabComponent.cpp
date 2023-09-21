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
	//// ���𰡸� ��� ���� ��, �ش� ��ü�� unclick �Ѵ�. 
	//else 
	//{
	//	isHavingObject = false;
	//	// click ���� Object�� nullptr�� �������ش�. 
	//	hitObject = nullptr;
	//}
}

void UGrabComponent::TargetingFurniture()
{
	//����Ʈ���̽��� ���
	FVector startLoc = player->hmdCam->GetComponentLocation();
	FVector endLoc = startLoc + player->hmdCam->GetForwardVector() * 1000;
	FHitResult hitInfo;
	const TArray<AActor*> IgnoreActor;
	FCollisionQueryParams param;
	param.AddIgnoredActor(GetOwner());
	int HitCount = 0;

	//������ �ι� ������ furniture�� movable�� false�� �ȴ�.
	//movable�� true��
	//MoveObject�� Ȱ��ȭ�ϰ�
	//movable�� false��
	//���󺹱��Ѵ�.

	//���� ���Ͱ� FurnitureActor���� Ȯ���Ѵ�.
	//FurnitureActor�� �¾Ҵٸ�
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

			//FurnitureActor�� ����ƽ�޽��� �ִ� RenderCustomDepth�� true�� �ٲ۴�.
			if (!furniture->movable)
			{
				//������ �ѹ� ������ furniture�� movable�� true�� �ٲٰ�
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
//	//// 3. Overlap ����� ����� ��
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
//	//����Ʈ���̽��� ����Ѵ�.
//	//�տ��� ���� ������ ����Ʈ���̽���
//	//������ ��� �Ǹ� ��´�.
//	//Physicshandle������Ʈ�� ĳ���Ϳ� �߰��Ѵ�.
//	//physicshandle->grab component at location with rotation
//	//isgrab? bool���� �߰��Ѵ�.
//	//release�� ������ bool���� true���
//	//physics handle���� releaseComponent�� �߰��ϰ� grab object�� false�� �ٲ۴�.
//}
//
//void UGrabComponent::ReleaseObject()
//{
//	//if (grabbedObject != nullptr)
//	//{
//	//	// ��ü�� �տ��� �и��ϰ�, ���� �ɷ��� Ȱ��ȭ�Ѵ�.
//	//	grabbedObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//	//	grabbedObject->boxcomp->SetSimulatePhysics(true);
//	//
//	//	// ��ü�� ������ ���⿡ ���� ��(����, ȸ����)�� ���Ѵ�.
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

