// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureList_Bed.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "EngineUtils.h"
#include "MyFurnitureActor.h"
#include "VRCharacter.h"
#include "CameraPawn.h"
#include <Kismet/GameplayStatics.h>



void UFurnitureList_Bed::NativeConstruct()
{
	Super::NativeConstruct();

	btn_spawn->OnClicked.AddDynamic(this, &UFurnitureList_Bed::SpawnFurniture);
	

	text_furniture->SetText(FText::FromString(TEXT("Blank")));
	//furnitureActor = CreateDefaultSubobject<AMyFurnitureActor>(TEXT("furnitureActor"));
	//cameraPawn = Cast<ACameraPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), cameraPawnClass));
}

FVector UFurnitureList_Bed::GetPlayerLocation()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			UE_LOG(LogTemp,Warning,TEXT("GETACTORLOCATION"))
			return PlayerPawn->GetActorLocation() + PlayerPawn->GetActorForwardVector() * 300;
		}
	}

	// Return an invalid location if the player's location cannot be retrieved.
	return FVector::ZeroVector;
}

void UFurnitureList_Bed::SpawnFurniture()
{
	UE_LOG(LogTemp,Warning,TEXT("Clicked button : %s"), *(this->text_furniture->GetText()).ToString());
	FVector playerLocation = GetPlayerLocation();

	AMyFurnitureActor* spawnedActor =  GetWorld()->SpawnActor<AMyFurnitureActor>(furnitureAsset,  playerLocation  , FRotator());
	//if(cameraPawn) cameraPawn->isGetFurniture = true;
	if(spawnedActor!=nullptr)
	{
		FString dir = "/Game/Furniture";
		dir.Append(FString::Printf(TEXT("%s"), *(text_assetDir->GetText()).ToString()));
		spawnedActor->assetDir = dir;
		UE_LOG(LogTemp,Warning,TEXT("dirAsset : %s"), *dir);
		spawnedActor->changeAsset();
	}
}
