// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomChoiceWidget.h"
#include <UMG/Public/Components/Button.h>
#include "VRCharacter.h"
#include "TelepoartDest_BedRoom.h"
#include <Kismet/GameplayStatics.h>

void URoomChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	btn_BedRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoBedRoom);
	btn_ChairRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoChairRoom);
	btn_DeskRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoDeskRoom);
	btn_ClosetRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoClosetRoom);
	btn_LightRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoLightRoom);
	btn_PartitionRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoPartitionRoom);

}

void URoomChoiceWidget::GoBedRoom()
{
	if (GetOwningPlayer())
	{
		AVRCharacter* Player = Cast<AVRCharacter>(GetOwningPlayer()->GetPawn());
		if (Player)
		{
			Player->TeleportDestination();
		}
	}
}

void URoomChoiceWidget::GoChairRoom()
{
	if (GetOwningPlayer())
	{
		AVRCharacter* Player = Cast<AVRCharacter>(GetOwningPlayer()->GetPawn());
		if (Player)
		{
			Player->TeleportDestination();
		}
	}
}

void URoomChoiceWidget::GoDeskRoom()
{
	if (GetOwningPlayer())
	{
		AVRCharacter* Player = Cast<AVRCharacter>(GetOwningPlayer()->GetPawn());
		if (Player)
		{
			Player->TeleportDestination();
		}
	}
}

void URoomChoiceWidget::GoClosetRoom()
{
	if (GetOwningPlayer())
	{
		AVRCharacter* Player = Cast<AVRCharacter>(GetOwningPlayer()->GetPawn());
		if (Player)
		{
			Player->TeleportDestination();
		}
	}
}

void URoomChoiceWidget::GoLightRoom()
{

}

void URoomChoiceWidget::GoPartitionRoom()
{

}
