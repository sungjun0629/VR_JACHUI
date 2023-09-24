// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR_JACHUI_API UGrabComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions);
	
	UPROPERTY(EditDefaultsOnly, Category=MySettings)
	float throwPower = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category=MySettings)
	float rotSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category=MySettings)
	class UHapticFeedbackEffect_Base* grab_Haptic;

private:
	class AVRCharacter* player;
	class ATestPickUp* grabbedObject;
	class AMyFurnitureActor* furniture;

	FVector prevLoc;
	FVector deltaLoc;
	FQuat prevRot;
	FQuat deltaRot;

	//UFUNCTION()
	//void GrabObject();
	//UFUNCTION()
	//void ReleaseObject();
	//UFUNCTION()
	//void RightHandMove();
	//
	//UPROPERTY(VisibleAnywhere, Category = MySettings)
	//bool IsGrab = false;

private:
	bool isHavingObject = false;

	UFUNCTION(BlueprintCallable)
	void TargetingFurniture();

	UFUNCTION(BlueprintCallable)
	void FurnitureMoveXY(const struct FInputActionValue& value);
	UFUNCTION(BlueprintCallable)
	void FurnitureMoveUpDown(const struct FInputActionValue& value);
	UFUNCTION(BlueprintCallable)
	void FurnitureRotate(const struct FInputActionValue& value);




	AActor* hitObject;
};
