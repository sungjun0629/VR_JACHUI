// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestPickUp.generated.h"

UCLASS()
class VR_JACHUI_API ATestPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

UPROPERTY(EditAnyWhere)
	class UBoxComponent* boxcomp;

UPROPERTY(EditAnyWhere)
	class UStaticMeshComponent* meshcomp;

UFUNCTION()
	void Grabbed(class USkeletalMeshComponent* handMesh);

};
