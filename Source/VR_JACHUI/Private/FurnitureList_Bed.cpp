// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureList_Bed.h"
#include "Components/TextBlock.h"



void UFurnitureList_Bed::NativeConstruct()
{
	Super::NativeConstruct();

	text_furniture->SetText(FText::FromString(TEXT("ho")));
}
