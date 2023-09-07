// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonParseLibrary.generated.h"



USTRUCT(BlueprintType)
struct FFurnitureJsonType
{
	GENERATED_USTRUCT_BODY()

public:
	FString UUID = TEXT("");
	FString name = TEXT("IKEA_CHAIR");
	FString brand = TEXT("");
	FString description = TEXT("");
	FString imgDir = TEXT("");
	FString assetDir = TEXT("");
	FString link = TEXT("");
	int32 furnitureNo = 0;
	float price = 0.f;
	bool isFD = true;
};
/**
 * 
 */
UCLASS()
class VR_JACHUI_API UJsonParseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static TArray<FFurnitureJsonType> FavJsonParse(const FString& originData);
};
