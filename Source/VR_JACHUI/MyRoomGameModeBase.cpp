// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRoomGameModeBase.h"
//#include "SJ_MyFavoriteWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/ListView.h"
#include <UMG/Public/Blueprint/UserWidget.h>
#include "MyFavoriteRequestActor.h"
#include "EngineUtils.h"
#include "FurnitureList_Bed.h"
#include "FavoriteCategoryWidget.h"
#include "List_BedRoom.h"

void AMyRoomGameModeBase::BeginPlay()
{
	FAVWidget = CreateWidget<UFavoriteCategoryWidget>(GetWorld(), FAVFurnitureWidget);
	//ListBedRoom = CreateWidget<UList_BedRoom>(GetWorld(), ListBedRoomWidget);

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
		FAVWidget->BP_ListBed->box->ClearChildren();
		if (FAVList.Num() > 0)
		{
			for (FFurnitureJsonType F : FAVList)
			{// FAVList�� �ִ� ��ŭ Addchild�� ���Ͽ� ������ �־��ش�. 
				FAVListEntity = CreateWidget<UFurnitureList_Bed>(GetWorld(), FAVFurnitureListEntity);
				UE_LOG(LogTemp,Warning,TEXT("add to child"));
				FAVWidget->BP_ListBed->box->AddChild(FAVListEntity);
				FAVListEntity->text_furniture->SetText(FText::FromString(F.name));
				FAVListEntity->text_assetDir->SetText(FText::FromString(F.assetDir));
				FAVListEntities.Add(FAVListEntity);
				FAVRequestActor->GETFurnitureImage(F.name);
			
			}
		}

	}
}

void AMyRoomGameModeBase::SetImageTexture(class UTexture2D* tex)
{
	if (FAVWidget != nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("SET IMAGE TEXTURE"));
		FAVListEntities[cnt++]->img_furniture->SetBrushFromTexture(tex);

	}
}
