// Fill out your copyright notice in the Description page of Project Settings.


#include "FavoriteCategoryWidget.h"
#include "Components/Button.h"
#include "MyFavoriteRequestActor.h"
#include "EngineUtils.h"
#include "../MyGameInstance.h"

void UFavoriteCategoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Bed->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteBed);
	btn_Chairs->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteChair);
	btn_Desk->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteTable);
	btn_Closet->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteCloset);
	btn_Light->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteLight);
	btn_Partition->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoritePartition);

	for (TActorIterator<AMyFavoriteRequestActor> it(GetWorld()); it; ++it)
	{
		MYFavoriteRequestActor = *it;
	}

	GI = Cast<UMyGameInstance>(GetGameInstance());
	userId = "sungjun1";
	//userId = GI->userInfo.userId;
}

void UFavoriteCategoryWidget::GETFavoriteBed()
{
	GETFavorite(userId, 1);
	UE_LOG(LogTemp,Warning,TEXT("%s"), *userId)
}

void UFavoriteCategoryWidget::GETFavoriteChair()
{
	GETFavorite(userId, 2);

}

void UFavoriteCategoryWidget::GETFavoriteTable()
{

}

void UFavoriteCategoryWidget::GETFavoriteCloset()
{

}

void UFavoriteCategoryWidget::GETFavoriteLight()
{

}

void UFavoriteCategoryWidget::GETFavoritePartition()
{

}

void UFavoriteCategoryWidget::GETFavorite(const FString myID, const int32 FurnitureNo)
{
	if (MYFavoriteRequestActor != nullptr)
	{
		MYFavoriteRequestActor->GETMyFavoritesFurniture(myID, FurnitureNo);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CAN'T GET FAVORITE %s FURNITURE. THERE IS NO REQUEST ACTOR"), *myID);
	}
}
