// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR_JACHUI_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions);

	UFUNCTION(BlueprintCallable)
    void GoingInteriorSpawn(const struct FInputActionValue& value);
   
    UPROPERTY(EditAnywhere)
    TSubclassOf<class ARoomTransferActor> room;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class AGoingMyRoomActor> GoingWidget;

private:
	class AVRCharacter* player;
	class AMyFurnitureActor* furniture;

	void Move(const struct FInputActionValue& value);
	void Rotate(const struct FInputActionValue& value);
	void RoomChoiceUIKey(const struct FInputActionValue& value);
	void FavoriteUIKey(const struct FInputActionValue& value);
	

		
};
