// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureEditorWidget.h"
#include "Components/Button.h"
#include "MyFurnitureActor.h"
#include <Kismet/GameplayStatics.h>

void UFurnitureEditorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Delete->OnClicked.AddDynamic(this, &UFurnitureEditorWidget::Delete);
	btn_Move->OnClicked.AddDynamic(this, &UFurnitureEditorWidget::Move);
	btn_Rotate->OnClicked.AddDynamic(this, &UFurnitureEditorWidget::Rotate);
	btn_FavoriteList->OnClicked.AddDynamic(this, &UFurnitureEditorWidget::AppearFavoriteList);
}

void UFurnitureEditorWidget::Delete()
{
	SpawnFurniture = Cast<AMyFurnitureActor>(UGameplayStatics::GetActorOfClass(GetWorld(),SpawnThings));
	//클릭되어있는 액터가 있다.
	//Delte 버튼을 누르면
	//Destroy Actor()를 시킨다.
}

void UFurnitureEditorWidget::Move()
{
	//클릭되어 있는 액터가 있다.
	//버튼을 누르면 움직일 수 있는 Move 노드들이 Visible로 바뀐다.
	//다시 누르면 Visibility를 hidden으로 바꾼다.
}

void UFurnitureEditorWidget::Rotate()
{
	//클릭되어 있는 액터가 있다.
	//버튼을 누르면 움직일 수 있는 Move 노드들이 Visible로 바뀐다.
	//다시 누르면 Visibility를 hidden으로 바꾼다.
}

void UFurnitureEditorWidget::AppearFavoriteList()
{
	//FavoriteList를 띄둔다.
	//버튼 다시 한번 더 누르면 FavoriteList 없앤다.

}

