// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLibrary.h"

TArray<FFurnitureJsonType> UJsonParseLibrary::FavJsonParse(const FString& originData)
{
	TArray<FFurnitureJsonType> parsedData; 
	FFurnitureJsonType FAVfurnitureInfo;

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(reader, result))
	{// Json ÇØµ¶ 
		const FString fieldName = "furnitureList";
		TArray<TSharedPtr<FJsonValue>> parsedDataArr = result->GetArrayField(*fieldName);

		for (TSharedPtr<FJsonValue> furnitureInfo : parsedDataArr)
		{
			FAVfurnitureInfo.UUID = furnitureInfo->AsObject()->GetStringField("UUID");
			FAVfurnitureInfo.name = furnitureInfo->AsObject()->GetStringField("name");
			FAVfurnitureInfo.brand = furnitureInfo->AsObject()->GetStringField("brand");
			FAVfurnitureInfo.description = furnitureInfo->AsObject()->GetStringField("description");
			FAVfurnitureInfo.imgDir = furnitureInfo->AsObject()->GetStringField("imgDir");
			FAVfurnitureInfo.assetDir = furnitureInfo->AsObject()->GetStringField("assetDir");
			FAVfurnitureInfo.link = furnitureInfo->AsObject()->GetStringField("link");
			FAVfurnitureInfo.furnitureNo = furnitureInfo->AsObject()->GetIntegerField("furnitureNo");
			FAVfurnitureInfo.price = furnitureInfo->AsObject()->GetNumberField("price");
			FAVfurnitureInfo.isFD = furnitureInfo->AsObject()->GetBoolField("FD");

			parsedData.Add(FAVfurnitureInfo);
		}
	}

	return parsedData;
}
