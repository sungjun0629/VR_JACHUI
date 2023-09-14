// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShowRoomGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VR_JACHUI_API AShowRoomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UFurnitureInformationUI> FurniutreInfoUI;
	
	void SetFurnitureDetailInfo(const TArray<FFurnitureJsonType> Info);
	void SetImageTexture(class UTexture2D* tex);

private:
	UPROPERTY()
	class UFurnitureInformationUI* FurInfoUI;

	UPROPERTY()
	class AFurnitureDetailRequestActor* FurDetailRequestActor; 
};
