// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FurnitureList_Bed.h"
#include "SJ_MyFavoriteWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API USJ_MyFavoriteWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_bed;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_chair;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_table;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_closet;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_light;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_partition;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = MySettings)
	class UTextBlock* name;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = MySettings)
	class UImage* furniture_image;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = MySettings)
	class UListView* List_FAV;

	UFUNCTION()
	void AddListView(class UFurnitureList_Bed* entity);

private:
	UFUNCTION()
	void GETFavoriteBed();
	UFUNCTION()
	void GETFavoriteChair();
	UFUNCTION()
	void GETFavoriteTable();
	UFUNCTION()
	void GETFavoriteCloset();
	UFUNCTION()
	void GETFavoriteLight();
	UFUNCTION()
	void GETFavoritePartition();

	UPROPERTY()
	class AMyFavoriteRequestActor* MYFavoriteRequestActor;

	void GETFavorite(const FString myID);

};
