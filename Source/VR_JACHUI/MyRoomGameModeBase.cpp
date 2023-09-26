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
#include "VRCharacter.h"
#include <UMG/Public/Components/WidgetComponent.h>

void AMyRoomGameModeBase::BeginPlay()
{
	FAVWidget = CreateWidget<UFavoriteCategoryWidget>(GetWorld(), FAVFurnitureWidget);
	//ListBedRoom = CreateWidget<UList_BedRoom>(GetWorld(), ListBedRoomWidget);
	player = Cast<AVRCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), VRCharacter));

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

	// 3D 상황
	if (player && player->FavoriteUI)
	{
		class UFavoriteCategoryWidget* FAVWidget3D = Cast<UFavoriteCategoryWidget>(player->FavoriteUI->GetUserWidgetObject());
		if (FAVWidget3D)
		{
			UE_LOG(LogTemp, Warning, TEXT("get FAVWidget3D"));
			FAVWidget3D->BP_ListBed->box->ClearChildren();
			if (FAVList.Num() > 0)
			{
				for (FFurnitureJsonType F : FAVList)
				{// FAVList�� �ִ� ��ŭ Addchild�� ���Ͽ� ������ �־��ش�. 
					FAVListEntity = CreateWidget<UFurnitureList_Bed>(GetWorld(), FAVFurnitureListEntity);
					UE_LOG(LogTemp, Warning, TEXT("add to child"));
					FAVWidget3D->BP_ListBed->box->AddChild(FAVListEntity);
					FAVListEntity->text_furniture->SetText(FText::FromString(F.name));
					FAVListEntity->text_assetDir->SetText(FText::FromString(F.assetDir));
					FAVListEntities.Add(FAVListEntity);
					FAVRequestActor->GETFurnitureImage(F.name);

				}
			}
		}
		else {
			UE_LOG(LogTemp,Warning,TEXT("failed to get widget"));
		}
	}



	// 2D 상황 -> 위젯에 띄운다. 
	//if (FAVWidget != nullptr)
	//{
	//	FAVWidget->BP_ListBed->box->ClearChildren();
	//	if (FAVList.Num() > 0)
	//	{
	//		for (FFurnitureJsonType F : FAVList)
	//		{// FAVList�� �ִ� ��ŭ Addchild�� ���Ͽ� ������ �־��ش�. 
	//			FAVListEntity = CreateWidget<UFurnitureList_Bed>(GetWorld(), FAVFurnitureListEntity);
	//			UE_LOG(LogTemp,Warning,TEXT("add to child"));
	//			FAVWidget->BP_ListBed->box->AddChild(FAVListEntity);
	//			FAVListEntity->text_furniture->SetText(FText::FromString(F.name));
	//			FAVListEntity->text_assetDir->SetText(FText::FromString(F.assetDir));
	//			FAVListEntities.Add(FAVListEntity);
	//			FAVRequestActor->GETFurnitureImage(F.name);
	//		
	//		}
	//	}
	//}


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

		UE_LOG(LogTemp,Warning,TEXT("have level data"));
		// 저장된 Asset을 spawn한다. 
		for (int i = 0; i < SG->AssetDir.Num(); i++)
		{
			FVector spawnLoc = SG->AssetLoc[i];
			FRotator spawnRot = SG->AssetRot[i];
			AMyFurnitureActor* spawnedActor =GetWorld()->SpawnActor<AMyFurnitureActor>(furnitureAsset, spawnLoc, spawnRot);
			spawnedActor->assetDir = SG->AssetDir[i];
			spawnedActor->belayed = true;
			spawnedActor->changeAsset();
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
		/*FSaveInfo savetest;
		savetest.dir = e->assetDir;
		savetest.loc = e->GetActorLocation();*/
		
		// SaveGame에 현재 가구 정보를 넣어준다. 
		SG->AssetKey.Add(e->GetName());
		SG->AssetDir.Add(e->assetDir);
		SG->AssetLoc.Add(e->GetActorLocation());
		SG->AssetRot.Add(e->GetActorRotation());

		// 추후 메모리 접근을 막기 위해 지운다. 
		// 추후 end UI에 넣어준다.
		SG->FurnitureInfo.Empty();
	}
	
	UGameplayStatics::SaveGameToSlot(SG, slotName, 0);

	
	
	for (FSaveInfo e : SG->LevelSaveStorage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Array Info Loc: %f, %f, %f "), e.loc.X, e.loc.Y, e.loc.Z);
	}
	UE_LOG(LogTemp, Warning, TEXT("Array Info Num: %d "), SG->LevelSaveStorage.Num());
	

}

void AMyRoomGameModeBase::SaveData(FString assetName, FVector assetLoc, FRotator assetRot)
{
	FString slotName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	for (int i = 0; i < SG->AssetKey.Num(); i++)
	{
		if (assetName.Contains(SG->AssetKey[i]))
		{
			SG->AssetLoc[i] = assetLoc;
			SG->AssetRot[i] = assetRot;
			UE_LOG(LogTemp,Warning,TEXT("asset Found, Change Info"))
			UGameplayStatics::SaveGameToSlot(SG, slotName, 0);
			return;
		}
		UE_LOG(LogTemp,Warning,TEXT("asset doesn't founded"))
	}

}
