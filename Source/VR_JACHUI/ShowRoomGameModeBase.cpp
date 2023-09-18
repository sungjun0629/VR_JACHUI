// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowRoomGameModeBase.h"
#include "FurnitureInformationUI.h"
#include "EngineUtils.h"
#include "JsonParseLibrary.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DetailUIActor.h"

void AShowRoomGameModeBase::BeginPlay()
{
	FurInfoUI = CreateWidget<UFurnitureInformationUI>(GetWorld(), FurniutreInfoUI);

	for (TActorIterator<ADetailUIActor> it(GetWorld()); it; ++it)
	{
		DetailActor = *it;
	}

	/*if (FurInfoUI != nullptr)
	{
		FurInfoUI->AddToViewport();
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	}*/
	
	for (TActorIterator<AFurnitureDetailRequestActor> it(GetWorld()); it; ++it)
	{
		FurDetailRequestActor = *it;
	}

	/*if (FurDetailRequestActor != nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Request Detail Info"));
		FurDetailRequestActor->GETFurnitureInfo("SM_Armchair");
	}*/
}


void AShowRoomGameModeBase::SetFurnitureDetailInfo(const TArray<FFurnitureJsonType> Info)
{

	if (FurInfoUI != nullptr)
	{
		if (Info.Num() > 0)
		{
			FurInfoUI->text_brandName->SetText(FText::FromString(Info[0].brand));
			FurInfoUI->text_furnitureName->SetText(FText::FromString(Info[0].name));
			FurInfoUI->text_description->SetText(FText::FromString(Info[0].description));
			FurInfoUI->text_furniturePrice->SetText(FText::FromString(FString::Printf(TEXT("%f"), Info[0].price)));
			//FurInfoUI->text_furnitureRank->SetText(FText::FromString(Info.price));
			FurDetailRequestActor->GETFurnitureImage(Info[0].name);
		}

	}

	if (DetailActor != nullptr && DetailActor->DetailUIWidget)
	{
		UE_LOG(LogTemp, Warning,TEXT("hi2"))

		UFurnitureInformationUI* furinfo = Cast<UFurnitureInformationUI>(DetailActor->DetailUIWidget->GetWidget());
		//DetailActor->DetailUIWidget->GetWidget()

		if (furinfo != nullptr)
		{
			furinfo->text_brandName->SetText(FText::FromString(Info[0].brand));
			furinfo->text_furnitureName->SetText(FText::FromString(Info[0].name));
			furinfo->text_description->SetText(FText::FromString(Info[0].description));
			furinfo->text_furniturePrice->SetText(FText::FromString(FString::Printf(TEXT("%f"), Info[0].price)));
			//FurInfoUI->text_furnitureRank->SetText(FText::FromString(Info.price));
			FurDetailRequestActor->GETFurnitureImage(Info[0].name);
		}
	}
}

void AShowRoomGameModeBase::SetImageTexture(class UTexture2D* tex)
{
	if (FurInfoUI != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SET IMAGE TEXTURE"));
		FurInfoUI->img_furniture->SetBrushFromTexture(tex);

	}

	UFurnitureInformationUI* furinfo = Cast<UFurnitureInformationUI>(DetailActor->DetailUIWidget->GetWidget());
	//DetailActor->DetailUIWidget->GetWidget()

	if (furinfo != nullptr)
	{
		furinfo->img_furniture->SetBrushFromTexture(tex);
	}
}

