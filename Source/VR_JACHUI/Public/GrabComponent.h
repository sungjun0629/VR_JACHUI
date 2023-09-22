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
	bool bFurnitureInputEnabled = false;

	void GetOrDeleteObject();

	UFUNCTION(BlueprintCallable)
	void TargetingFurniture();

	void MoveObjectForward(const struct FInputActionValue& value);

	void MoveObjectBackward(const struct FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void FurnitureMoveForward(const struct FInputActionValue& value);
	UFUNCTION(BlueprintCallable)
	void FurnitureMoveBackward(const struct FInputActionValue& value);
	UFUNCTION(BlueprintCallable)
	void FurnitureMoveRight(const struct FInputActionValue& value);
	UFUNCTION(BlueprintCallable)
	void FurnitureMoveLeft(const struct FInputActionValue& value);
	UFUNCTION(BlueprintCallable)
	void FurnitureMoveUp(const struct FInputActionValue& value);
	UFUNCTION(BlueprintCallable)
	void FurnitureMoveDown(const struct FInputActionValue& value);

	AActor* hitObject;
};
