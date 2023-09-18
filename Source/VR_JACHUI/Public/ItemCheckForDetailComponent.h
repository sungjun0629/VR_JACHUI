// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemCheckForDetailComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR_JACHUI_API UItemCheckForDetailComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemCheckForDetailComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions);

	/*UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UFurnitureInformationUI> FurniutreInfoUI;*/

	UPROPERTY()
	class ADetailUIActor* DetailUI;

private:
	bool isHavingObject = false;

	void CheckItem();
	
	class AVRCharacter* player;

	AActor* hitObject;

	UPROPERTY()
	class UFurnitureInformationUI* FurInfoUI;

	UPROPERTY()
	class AFurnitureDetailRequestActor* FurDetailRequestActor; 

	UPROPERTY()
	class AShowRoomGameModeBase* ShowRoomGM;
};
