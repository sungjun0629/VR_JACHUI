// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FurnitureFavoriteActor.generated.h"

UCLASS()
class VR_JACHUI_API AFurnitureFavoriteActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFurnitureFavoriteActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = MySettings)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = MySettings)
	class UWidgetComponent* FavoriteUI;

};
