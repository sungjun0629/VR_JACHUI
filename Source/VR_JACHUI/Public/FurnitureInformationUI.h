// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FurnitureInformationUI.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API UFurnitureInformationUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UCheckBox* box_Favorite;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UImage* img_furniture;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UTextBlock* text_brandName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UTextBlock* text_furnitureName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UTextBlock* text_furniturePrice;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UTextBlock* text_description;



	//UPROPERTY(VisibleAnywhere)
	//void AddFavoriteCategory();
};
