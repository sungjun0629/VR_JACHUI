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
#include <Kismet/GameplayStatics.h>
#include "MapSaveGame.h"
#include "MyFurnitureActor.h"

void AMyRoomGameModeBase::BeginPlay()
{
	FAVWidget = CreateWidget<UFavoriteCategoryWidget>(GetWorld(), FAVFurnitureWidget);
	//ListBedRoom = CreateWidget<UList_BedRoom>(GetWorld(), ListBedRoomWidget);

	if (FAVWidget != nullptr)
	{
		FAVWidget->AddToViewport();
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		//GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	}

	for (TActorIterator<AMyFavoriteRequestActor> it(GetWorld()); it; ++it)
	{
		FAVRequestActor = *it;
	}

	InitLevelSaveData();
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

void AMyRoomGameModeBase::InitLevelSaveData()
{
	FString slotName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	bool isSaved = UGameplayStatics::DoesSaveGameExist(slotName, 0);
	if (isSaved) 
	{
		SG = Cast<UMapSaveGame>(UGameplayStatics::LoadGameFromSlot(slotName,0));
		UE_LOG(LogTemp,Warning,TEXT("have level data size : %d "), SG->LevelSaveStorage.Num());
		UE_LOG(LogTemp,Warning,TEXT("age: %d "), SG->age);
		
		for (FSaveInfo e : SG->LevelSaveStorage)
		{
			UE_LOG(LogTemp,Warning,TEXT("furniture Name : %s "), *e.dir);
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("doesn't have level data"));
		SG = Cast<UMapSaveGame>(UGameplayStatics::CreateSaveGameObject(MapSaveGame));
		UGameplayStatics::SaveGameToSlot(SG, UGameplayStatics::GetCurrentLevelName(GetWorld()), 0);
	}
}

void AMyRoomGameModeBase::SaveLevelData()
{
	FString slotName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	for (AMyFurnitureActor* e : SG->FurnitureInfo)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s"), *e->assetDir);
		//SG->saveInfo.Set("", e->GetActorLocation());
		// Furniture에 대한 정보를 입력해준다. 
		SG->LevelSaveStorage.Add(SG->saveInfo);
	}
	//if(SG) SG->LevelSaveStorage.Empty();
	//SG->age = 8;
	UGameplayStatics::SaveGameToSlot(SG, slotName, 0);

	
	{
		//SG = Cast<UMapSaveGame>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
		for (FSaveInfo e : SG->LevelSaveStorage)
		{
			UE_LOG(LogTemp, Warning, TEXT("Array Info : %s "), *e.dir);
		}
			UE_LOG(LogTemp, Warning, TEXT("Array Info : %d "), SG->LevelSaveStorage.Num());
	}

}
