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

	void MakeRotate(float value);

	void DragNDrop();

	bool CatchFurniture();

	void Rotate();

	void ChangeSpawnLoc();

	bool CanDrop();

	void ClickButton();

	void DebugLine();

	void SpeedUP();

	void SpeedDOWN();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, Category="MySettings")
	class UCapsuleComponent* ColliComp;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category="MySettings|Components")
	class UMotionControllerComponent* rightMotionController;

	UPROPERTY(EditAnywhere, Category="MySettings|Components")
	class USkeletalMeshComponent* rightHand;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings|Components")
	class UWidgetInteractionComponent* rightWidgetPointer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	class UWidgetComponent* FavoriteUI;

	UPROPERTY(EditAnywhere, Category="MySettings")
	float speed = 100.0f;

	UPROPERTY(EditAnywhere, Category="MySettings")
	float distSpeed = 30.0f;

	UPROPERTY(EditAnywhere, Category="MySettings")
	bool isGetFurniture = false;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	float rotSpeed = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	class UNiagaraSystem* dustEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	TSubclassOf<class APlayerSpawnActor> playerSpawnActor;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	TSubclassOf<class AVRCharacter> VRCharacter;


	class AMyFurnitureActor* havingObject;

	class APlayerController* pc;

	class APlayerSpawnActor* spawnActor; 

	class AVRCharacter* player; 

	FHitResult hitInfo;



private:	
	FVector Direction;

	bool isRotate = false;

	class AMyRoomGameModeBase* RoomGM;


};
