// Fill out your copyright notice in the Description page of Project Settings.


#include "GoingMyRoomWidget.h"
#include <UMG/Public/Components/Button.h>
#include "VRCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "RoomTransferActor.h"
#include "GoingMyRoomActor.h"

void UGoingMyRoomWidget::NativeConstruct()
{
	btn_Yes->OnClicked.AddDynamic(this, &UGoingMyRoomWidget::TransferLevel);
	btn_No->OnClicked.AddDynamic(this, &UGoingMyRoomWidget::DestroyActor);
}

void UGoingMyRoomWidget::TransferLevel()
{
	//FName LevelName =TEXT("InteriorMap");
	//UGameplayStatics::OpenLevel(GetWorld(),LevelName);
	GetWorld()->GetFirstPlayerController()->ClientTravel("/Game/Maps/InteriorMap", ETravelType::TRAVEL_Absolute);

}

void UGoingMyRoomWidget::DestroyActor()
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(world, ARoomTransferActor::StaticClass(), FoundActors);
		UGameplayStatics::GetAllActorsOfClass(world, AGoingMyRoomActor::StaticClass(), FoundActors);

		for (AActor* Actor : FoundActors)
		{
			Actor->Destroy();
		}
	}
}
