// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureList_Bed.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "EngineUtils.h"
#include "MyFurnitureActor.h"



void UFurnitureList_Bed::NativeConstruct()
{
	Super::NativeConstruct();

	btn_spawn->OnClicked.AddDynamic(this, &UFurnitureList_Bed::SpawnFurniture);
	

	text_furniture->SetText(FText::FromString(TEXT("Blank")));
	//furnitureActor = CreateDefaultSubobject<AMyFurnitureActor>(TEXT("furnitureActor"));
	
}

void UFurnitureList_Bed::SpawnFurniture()
{
	UE_LOG(LogTemp,Warning,TEXT("Clicked button : %s"), *(this->text_furniture->GetText()).ToString());

	AMyFurnitureActor* spawnedActor =  GetWorld()->SpawnActor<AMyFurnitureActor>(furnitureAsset, FVector(1200,390,0), FRotator());
	if(spawnedActor!=nullptr)
	{
		spawnedActor->assetDir = "/Game/Furniture/Chair/SM_Chair_2";
		spawnedActor->changeAsset();
	}
}
