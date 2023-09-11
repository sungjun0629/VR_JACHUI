// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomChoiceWidget.h"
#include <UMG/Public/Components/Button.h>

void URoomChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	btn_BedRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoBedRoom);
	btn_ChairRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoChairRoom);
	btn_DeskRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoDeskRoom);
	btn_ClosetRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoClosetRoom);
	btn_LightRoom->OnClicked.AddDynamic(this, &URoomChoiceWidget::GoLightRoom);
	btn_PartitionRoom->OnHovered.AddDynamic(this, &URoomChoiceWidget::GoPartitionRoom);
	btn_BedRoom->OnHovered.AddDynamic(this, &URoomChoiceWidget::GoBedRoom);
	btn_ChairRoom->OnHovered.AddDynamic(this, &URoomChoiceWidget::GoChairRoom);
	btn_DeskRoom->OnHovered.AddDynamic(this, &URoomChoiceWidget::GoDeskRoom);
	btn_ClosetRoom->OnHovered.AddDynamic(this, &URoomChoiceWidget::GoClosetRoom);
	btn_LightRoom->OnHovered.AddDynamic(this, &URoomChoiceWidget::GoLightRoom);
	btn_PartitionRoom->OnHovered.AddDynamic(this, &URoomChoiceWidget::GoPartitionRoom);
}

void URoomChoiceWidget::GoBedRoom()
{

}

void URoomChoiceWidget::GoChairRoom()
{

}

void URoomChoiceWidget::GoDeskRoom()
{

}

void URoomChoiceWidget::GoClosetRoom()
{

}

void URoomChoiceWidget::GoLightRoom()
{

}

void URoomChoiceWidget::GoPartitionRoom()
{

}
