// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomTransferActor.generated.h"

UCLASS()
class VR_JACHUI_API ARoomTransferActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomTransferActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = MySettings)
	class UBoxComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = MySettings)
	class UStaticMeshComponent* Walls;

	UPROPERTY(VisibleAnywhere, Category = MySettings)
	class UStaticMeshComponent* floor;

	UPROPERTY(VisibleAnywhere, Category = MySettings)
	class URotatingMovementComponent* RotateMove;

};
