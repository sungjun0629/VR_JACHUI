// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomName.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API URoomName : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	UTextBlock* BedRoom;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	UTextBlock* ChairRoom;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	UTextBlock* DeskRoom;
};
