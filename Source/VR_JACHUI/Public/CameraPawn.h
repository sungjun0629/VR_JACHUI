// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class VR_JACHUI_API ACameraPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Horizontal(float value);

	void Vertical(float value);

	void MakeDistance(float value);

	void DragNDrop();

	bool CatchFurniture();

	void Rotate();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category="MySettings")
	float speed = 100.0f;

	UPROPERTY(EditAnywhere, Category="MySettings")
	float distSpeed = 30.0f;

	UPROPERTY(EditAnywhere, Category="MySettings")
	bool isGetFurniture = false;
	
	class AMyFurnitureActor* havingObject;

	class APlayerController* pc;

private:	
	FVector Direction;

	bool isRotate = false;


};
