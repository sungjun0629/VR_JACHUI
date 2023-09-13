// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRoomGameModeBase.h"
#include "SJ_MyFavoriteWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include <UMG/Public/Blueprint/UserWidget.h>
#include "MyFavoriteRequestActor.h"
#include "EngineUtils.h"
#include "FurnitureList_Bed.h"

void AMyRoomGameModeBase::BeginPlay()
{
	FAVWidget = CreateWidget<USJ_MyFavoriteWidget>(GetWorld(), FAVFurnitureWidget);

	if (FAVWidget != nullptr)
	{
		//FAVWidget->AddToViewport();
// 		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
// 		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
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
		if (FAVList.Num() > 0)
		{
			for (FFurnitureJsonType F : FAVList)
			{// FAVList에 있는 만큼 Addchild를 통하여 위젯에 넣어준다. 
				FAVListEntity = CreateWidget<UFurnitureList_Bed>(GetWorld(), FAVFurnitureListEntity);
				//FAVListEntity2 = CreateWidget<UFurnitureList_Bed>(GetWorld(), FAVFurnitureListEntity);
				UE_LOG(LogTemp,Warning,TEXT("name : %s"), *F.name);
				UE_LOG(LogTemp,Warning,TEXT("num : %d"), ret++);
				FAVListEntity->changeText();
				FAVWidget->AddListView(FAVListEntity);
				//FAVRequestActor->GETFurnitureImage(F.name);
				
				//FAVWidget->List_FAV->AddItem(FAVListEntity2);
			}
		}

		//FAVWidget->name->SetText(FText::FromString(FAVList[0].name));
		//FAVRequestActor->GETFurnitureImage("ikea_sofa");

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
