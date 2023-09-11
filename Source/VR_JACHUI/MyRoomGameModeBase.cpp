// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRoomGameModeBase.h"
#include "SJ_MyFavoriteWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include <UMG/Public/Blueprint/UserWidget.h>
#include "MyFavoriteRequestActor.h"
#include "EngineUtils.h"

void AMyRoomGameModeBase::BeginPlay()
{
	FAVWidget = CreateWidget<USJ_MyFavoriteWidget>(GetWorld(), FAVFurnitureWidget);

	if (FAVWidget != nullptr)
	{
		FAVWidget->AddToViewport();
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	}

	for (TActorIterator<AMyFavoriteRequestActor> it(GetWorld()); it; ++it)
	{
		FAVRequestActor = *it;
	}
}

void AMyRoomGameModeBase::SetFAVFurnitureList(const TArray<FFurnitureJsonType> FAVList)
{
	if (FAVWidget != nullptr)
	{
		if(FAVList.Num()>0)
		FAVWidget->name->SetText(FText::FromString(FAVList[0].name));
		FAVRequestActor->GETFurnitureImage(FAVList[0].name);

	}
	
	// List일 때
	//for (FFurnitureJsonType Furni : FAVList)
	//{
	//	// 이미지 GET을 요청한다. 
	//	FAVRequestActor->GETFurnitureImage(Furni.name);

	//}
}

void AMyRoomGameModeBase::SetImageTexture(class UTexture2D* tex)
{
	if (FAVWidget != nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("SET IMAGE TEXTURE"));
		FAVWidget->furniture_image->SetBrushFromTexture(tex);
	}
}
