// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRoomGameModeBase.h"
#include "SJ_MyFavoriteWidget.h"
#include "Components/TextBlock.h"
#include <UMG/Public/Blueprint/UserWidget.h>

void AMyRoomGameModeBase::BeginPlay()
{
	FAVWidget = CreateWidget<USJ_MyFavoriteWidget>(GetWorld(), FAVFurnitureWidget);

	if (FAVWidget != nullptr)
	{
		FAVWidget->AddToViewport();
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	}
}

void AMyRoomGameModeBase::SetFAVFurnitureList(const TArray<FFurnitureJsonType> FAVList)
{
	if (FAVWidget != nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("change Name"));
		FAVWidget->name->SetText(FText::FromString(FAVList[0].name));
	}
}
