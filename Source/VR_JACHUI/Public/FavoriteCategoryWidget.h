// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FavoriteCategoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API UFavoriteCategoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Bed;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Chairs;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Desk;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Closet;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Light;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Partition;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Export;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Capture;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings, BlueprintReadWrite)
	class UWidgetSwitcher* ListSwitch;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings, BlueprintReadWrite)
	class UList_BedRoom* BP_ListBed;

	FString userId; 

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

	void GETFavorite(const FString myID, const int32 FurnitureNo);

	UPROPERTY()
	 class UMyGameInstance* GI;

};
