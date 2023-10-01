// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomLight.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API URoomLight : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UTextBlock* Title;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UTextBlock* Time;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UTextBlock* Light;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UTextBlock* Class;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class USlider* TimeSlider;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UButton* btn_ON;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UButton* btn_OFF;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UButton* btn_Exit;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UButton* btn_class1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UButton* btn_class2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = RoomLight)
		class UButton* btn_class3;

	UFUNCTION()
	void LightOn();

	UFUNCTION()
	void LightOff();

	UFUNCTION()
	void ChangeClass1();

	UFUNCTION()
	void ChangeClass2();

	UFUNCTION()
	void ChangeClass3();

	UFUNCTION()
	void ExitLightUI();
	



};
