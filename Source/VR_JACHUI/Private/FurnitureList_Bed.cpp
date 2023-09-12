// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureList_Bed.h"
#include "Components/TextBlock.h"



void UFurnitureList_Bed::NativeConstruct()
{
	Super::NativeConstruct();

	text_furniture->SetText(FText::FromString(TEXT("ho")));
	UE_LOG(LogTemp, Warning, TEXT("entity starts"));
}

void UFurnitureList_Bed::changeText()
{
	UE_LOG(LogTemp,Warning,TEXT("before text : %s"), *(text_furniture->GetText()).ToString())
	text_furniture->SetText(FText::FromString(TEXT("ho2")));
	UE_LOG(LogTemp,Warning,TEXT("after text : %s"), *(text_furniture->GetText()).ToString())
}
