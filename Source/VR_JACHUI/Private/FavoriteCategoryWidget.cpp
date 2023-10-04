// Fill out your copyright notice in the Description page of Project Settings.


#include "FavoriteCategoryWidget.h"
#include "Components/Button.h"
#include "MyFavoriteRequestActor.h"
#include "EngineUtils.h"
#include "../MyGameInstance.h"
#include "../MyRoomGameModeBase.h"
#include <Engine/Engine.h>

void UFavoriteCategoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Bed->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteBed);
	btn_Chairs->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteChair);
	btn_Desk->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteTable);
	btn_Closet->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteCloset);
	btn_Light->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoriteLight);
	btn_Partition->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::GETFavoritePartition);
	btn_Export->OnClicked.AddDynamic(this, &UFavoriteCategoryWidget::SaveLevel);


	for (TActorIterator<AMyFavoriteRequestActor> it(GetWorld()); it; ++it)
	{
		MYFavoriteRequestActor = *it;
	}

	GI = Cast<UMyGameInstance>(GetGameInstance());
	RoomGM = GetWorld()->GetAuthGameMode<AMyRoomGameModeBase>();
	userId = "sungjun1";
	//userId = GI->userInfo.userId;
}

void UFavoriteCategoryWidget::GETFavoriteBed()
{
	GETFavorite(userId, 1);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "GETFavorite");
	}
	
}

void UFavoriteCategoryWidget::GETFavoriteChair()
{
	GETFavorite(userId, 2);

}

void UFavoriteCategoryWidget::GETFavoriteTable()
{
	GETFavorite(userId, 3);
}

void UFavoriteCategoryWidget::GETFavoriteCloset()
{
	GETFavorite(userId, 4);
}

void UFavoriteCategoryWidget::GETFavoriteLight()
{
	GETFavorite(userId, 5);
}

void UFavoriteCategoryWidget::GETFavoritePartition()
{
	GETFavorite(userId, 6);
}

void UFavoriteCategoryWidget::SaveLevel()
{
	UE_LOG(LogTemp,Warning,TEXT("Save Level"));
	if(RoomGM) RoomGM->SaveLevelData();
}

void UFavoriteCategoryWidget::GETFavorite(const FString myID, const int32 FurnitureNo)
{
	if (MYFavoriteRequestActor != nullptr)
	{
		MYFavoriteRequestActor->GETMyFavoritesFurniture(myID, FurnitureNo);
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "GETFavorite");
		}*/
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CAN'T GET FAVORITE %s FURNITURE. THERE IS NO REQUEST ACTOR"), *myID);
	}
}
