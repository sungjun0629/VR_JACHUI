// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_MyFavoriteWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "EngineUtils.h"
#include "MyFavoriteRequestActor.h"
#include "FurnitureList_Bed.h"



void USJ_MyFavoriteWidget::NativeConstruct()
{

	Super::NativeConstruct();

	btn_bed->OnClicked.AddDynamic(this, &USJ_MyFavoriteWidget::GETFavoriteBed);
	btn_chair->OnClicked.AddDynamic(this, &USJ_MyFavoriteWidget::GETFavoriteChair);
	btn_table->OnClicked.AddDynamic(this, &USJ_MyFavoriteWidget::GETFavoriteTable);
	btn_closet->OnClicked.AddDynamic(this, &USJ_MyFavoriteWidget::GETFavoriteCloset);
	btn_light->OnClicked.AddDynamic(this, &USJ_MyFavoriteWidget::GETFavoriteLight);
	btn_partition->OnClicked.AddDynamic(this, &USJ_MyFavoriteWidget::GETFavoritePartition);

	for (TActorIterator<AMyFavoriteRequestActor> it(GetWorld()); it; ++it)
	{
		MYFavoriteRequestActor = *it;
	}
}

void USJ_MyFavoriteWidget::GETFavoriteBed()
{
	GETFavorite("first");
}

void USJ_MyFavoriteWidget::GETFavoriteChair()
{
	//GETFavorite(2);
}

void USJ_MyFavoriteWidget::GETFavoriteTable()
{
	//GETFavorite(3);
}

void USJ_MyFavoriteWidget::GETFavoriteCloset()
{
	//GETFavorite(4);
}

void USJ_MyFavoriteWidget::GETFavoriteLight()
{
	//GETFavorite(5);
}

void USJ_MyFavoriteWidget::GETFavoritePartition()
{
	//GETFavorite(6);
}

void USJ_MyFavoriteWidget::AddListView(class UFurnitureList_Bed* entity)
{
	List_FAV->AddItem(entity);
}

void USJ_MyFavoriteWidget::GETFavorite(const FString myID)
{
	if (MYFavoriteRequestActor != nullptr)
	{
		MYFavoriteRequestActor->GETMyFavoritesFurniture(myID);
		UE_LOG(LogTemp,Warning,TEXT("TRYING GET FAVORITE %s FURNITURE"), *myID);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("CAN'T GET FAVORITE %s FURNITURE. THERE IS NO REQUEST ACTOR"), *myID);
	}
}
