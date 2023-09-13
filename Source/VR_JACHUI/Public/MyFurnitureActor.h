// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFurnitureActor.generated.h"

UCLASS()
class VR_JACHUI_API AMyFurnitureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFurnitureActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category=MySetting)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, Category=MySetting)
	class UStaticMeshComponent* furnitureMesh;

	FString assetDir = "/Game/Furniture/Bed/SM_Bed";

	void changeAsset();
};
