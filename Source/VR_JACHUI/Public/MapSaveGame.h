// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
//#include "Containers/Pair.h"
#include "MapSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSaveInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FString dir = TEXT("");
	FVector loc = FVector();

	FORCEINLINE void Set(FString uID, FVector uName) { dir = uID; loc = uName; }
};
/**
 * 
 */
UCLASS()
class VR_JACHUI_API UMapSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	FSaveInfo saveInfo;

	UMapSaveGame();

	UPROPERTY(EditDefaultsOnly)
	TArray<class AMyFurnitureActor*> FurnitureInfo;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FSaveInfo> LevelSaveStorage;

	UPROPERTY(EditDefaultsOnly)
	int32 age;

};
