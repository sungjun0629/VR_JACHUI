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
	TSubclassOf<class USJ_MyFavoriteWidget> FAVFurnitureWidget;

	void SetFAVFurnitureList(const TArray<FFurnitureJsonType> FAVList);

private:
	class USJ_MyFavoriteWidget* FAVWidget;

};
