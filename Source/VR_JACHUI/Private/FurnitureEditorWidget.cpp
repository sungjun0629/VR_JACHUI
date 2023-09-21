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
	//Ŭ���Ǿ��ִ� ���Ͱ� �ִ�.
	//Delte ��ư�� ������
	//Destroy Actor()�� ��Ų��.
}

void UFurnitureEditorWidget::Move()
{
	//Ŭ���Ǿ� �ִ� ���Ͱ� �ִ�.
	//��ư�� ������ ������ �� �ִ� Move ������ Visible�� �ٲ��.
	//�ٽ� ������ Visibility�� hidden���� �ٲ۴�.
}

void UFurnitureEditorWidget::Rotate()
{
	//Ŭ���Ǿ� �ִ� ���Ͱ� �ִ�.
	//��ư�� ������ ������ �� �ִ� Move ������ Visible�� �ٲ��.
	//�ٽ� ������ Visibility�� hidden���� �ٲ۴�.
}

void UFurnitureEditorWidget::AppearFavoriteList()
{
	//FavoriteList�� ��д�.
	//��ư �ٽ� �ѹ� �� ������ FavoriteList ���ش�.

}

