// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SJ_MyFavoriteWidget.h"
#include "JsonParseLibrary.h"
#include "MyRoomGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API AMyRoomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UFavoriteCategoryWidget> FAVFurnitureWidget;
	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UFurnitureList_Bed> FAVFurnitureListEntity;
	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UMapSaveGame> MapSaveGame;
	/*UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UList_BedRoom> ListBedRoomWidget;*/
	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class AMyFurnitureActor> furnitureAsset;

	void SetFAVFurnitureList(const TArray<FFurnitureJsonType> FAVList);
	void SetImageTexture(class UTexture2D* tex);
	void InitLevelSaveData();
	void SaveLevelData();
	void SaveData(FString assetName , FVector assetLoc, FRotator assetRot);
	int32 cnt = 0; 

	UPROPERTY()
	class UMapSaveGame* SG;

private:
	UPROPERTY()
	class UFavoriteCategoryWidget* FAVWidget;
	
	UPROPERTY()
	class AMyFavoriteRequestActor* FAVRequestActor; 
	
	// 버튼 클릭 시 여러 actor가 스폰되지 않도록
	UPROPERTY()
	class AMyFurnitureActor* furActor;

	UPROPERTY()
	class UFurnitureList_Bed* FAVListEntity;

	TArray<class UFurnitureList_Bed*> FAVListEntities;

};
