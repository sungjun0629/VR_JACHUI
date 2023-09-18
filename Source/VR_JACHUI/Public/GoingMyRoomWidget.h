// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoingMyRoomWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API UGoingMyRoomWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UButton* CircleButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UButton* btn_Yes;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UButton* btn_No;

	UFUNCTION()
	void TransferLevel();

	UFUNCTION()
	void DestroyActor();
	
};
