// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FurnitureList_Bed.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API UFurnitureList_Bed : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = MySettings)
	class UTextBlock* text_furniture;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = MySettings)
	class UImage* img_furniture;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = MySettings)
	class UButton* btn_spawn;

	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class AMyFurnitureActor> furnitureAsset;

	UPROPERTY(EditAnywhere, Category = MySettings)
	class AMyFurnitureActor* furnitureActor;

private:
	UFUNCTION()
	void SpawnFurniture();
	

};
