// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomChoiceWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API URoomChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UTextBlock* Text;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UButton* btn_BedRoom;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UButton* btn_ChairRoom;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UButton* btn_DeskRoom;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UButton* btn_ClosetRoom;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UButton* btn_LightRoom;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomChoice)
	class UButton* btn_PartitionRoom;

	UFUNCTION()
	void GoBedRoom();

	UFUNCTION()
	void GoChairRoom();

	UFUNCTION()
	void GoDeskRoom();

	UFUNCTION()
	void GoClosetRoom();

	UFUNCTION()
	void GoLightRoom();

	UFUNCTION()
	void GoPartitionRoom();

};
