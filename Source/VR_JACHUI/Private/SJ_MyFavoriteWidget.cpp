// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_MyFavoriteWidget.h"
#include "Components/Button.h"
#include "EngineUtils.h"
#include "MyFavoriteRequestActor.h"



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
	GETFavorite(1);
}

void USJ_MyFavoriteWidget::GETFavoriteChair()
{
	GETFavorite(2);
}

void USJ_MyFavoriteWidget::GETFavoriteTable()
{
	GETFavorite(3);
}

void USJ_MyFavoriteWidget::GETFavoriteCloset()
{
	GETFavorite(4);
}

void USJ_MyFavoriteWidget::GETFavoriteLight()
{
	GETFavorite(5);
}

void USJ_MyFavoriteWidget::GETFavoritePartition()
{
	GETFavorite(6);
}

void USJ_MyFavoriteWidget::GETFavorite(const int32 furnitureNo)
{
	if (MYFavoriteRequestActor != nullptr)
	{
		MYFavoriteRequestActor->GETMyFavoritesFurniture(furnitureNo);
		UE_LOG(LogTemp,Warning,TEXT("TRYING GET FAVORITE %d FURNITURE"), furnitureNo);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("CAN'T GET FAVORITE %d FURNITURE. THERE IS NO REQUEST ACTOR"), furnitureNo);
	}
}
