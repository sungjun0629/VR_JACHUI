// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomChoiceActor.generated.h"

UCLASS()
class VR_JACHUI_API ARoomChoiceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomChoiceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = Base)
	class UWidgetComponent* Choice;

	UPROPERTY(EditAnywhere, Category = Base)
	TSubclassOf<class UUserWidget> roomChoice_Widget;

};
