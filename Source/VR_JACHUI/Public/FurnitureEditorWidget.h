// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FurnitureEditorWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API UFurnitureEditorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_FavoriteList;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Delete;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Move;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_Rotate;

	UFUNCTION()
	void Delete();

	UFUNCTION()
	void Move();

	UFUNCTION()
	void AppearFavoriteList();

	UFUNCTION()
	void Rotate();

	UPROPERTY(EditDefaultsOnly, Category=MySetting)
	class AMyFurnitureActor* SpawnFurniture;

	UPROPERTY(EditAnywhere, Category = MySettings)
	TSubclassOf<class AMyFurnitureActor> SpawnThings;
};
