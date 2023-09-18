// Fill out your copyright notice in the Description page of Project Settings.

#include "GrabComponent.h"
#include "VRCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "MotionControllerComponent.h"
#include "TestPickUp.h"
#include "Components/TextRenderComponent.h"
#include <Components/BoxComponent.h>


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

	if (grabbedObject != nullptr)
	{
		deltaLoc = player->rightMotionController->GetComponentLocation() - prevLoc;
		prevLoc = player->rightMotionController->GetComponentLocation();

		deltaRot = player->rightMotionController->GetComponentQuat() - prevRot.Inverse();
		prevRot = player->rightMotionController->GetComponentQuat();
	}

}

void UGrabComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[3], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
	enhancedInputComponent->BindAction(inputActions[3], ETriggerEvent::Completed, this, &UGrabComponent::ReleaseObject);
}

void UGrabComponent::GrabObject()
{
	if (grabbedObject != nullptr)
	{
		return;
	}	
	// 3. Overlap ����� ����� ��
	TArray<FOverlapResult> hitInfos;
	FVector startLoc = player->rightHand->GetComponentLocation();

	if (GetWorld()->OverlapMultiByProfile(hitInfos, startLoc, FQuat::Identity, FName("PickUp"), FCollisionShape::MakeSphere(20)))
	{
		for (const FOverlapResult& hitInfo : hitInfos)
		{
			if (ATestPickUp* pickObj = Cast<ATestPickUp>(hitInfo.GetActor()))
			{
				pickObj->Grabbed(player->rightHand);
				grabbedObject = pickObj;

				player->pc->PlayHapticEffect(grab_Haptic, EControllerHand::Right, 1.0f, false);
				break;
			}
		}
	}

	//DrawDebugSphere(GetWorld(), startLoc, 20, 30, FColor::Green, false, 1.0f);
}

void UGrabComponent::ReleaseObject()
{
	if (grabbedObject != nullptr)
	{
		// ��ü�� �տ��� �и��ϰ�, ���� �ɷ��� Ȱ��ȭ�Ѵ�.
		grabbedObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		grabbedObject->boxcomp->SetSimulatePhysics(true);

		// ��ü�� ������ ���⿡ ���� ��(����, ȸ����)�� ���Ѵ�.
// 		if (!deltaLoc.IsNearlyZero())
// 		{
// 			grabbedObject->boxcomp->AddImpulse(deltaLoc.GetSafeNormal() * throwPower);
// 			grabbedObject->boxcomp->AddTorqueInRadians(deltaRot.GetRotationAxis() * rotSpeed);
// 		}

		grabbedObject = nullptr;
	}
}

void UGrabComponent::RightHandMove(const struct FInputActionValue& value)
{
	FVector direction = value.Get<FVector>();
	player->rightMotionController->SetRelativeLocation(player->rightMotionController->GetRelativeLocation() + direction.GetSafeNormal());
}

