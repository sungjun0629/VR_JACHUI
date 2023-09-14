// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "MyFavoriteRequestActor.generated.h"

UCLASS()
class VR_JACHUI_API AMyFavoriteRequestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFavoriteRequestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GETMyFavoritesFurniture(const FString myID, const int32 FurnitureNo);
	void GETFurnitureImage(const FString furnitureName);

private:
	void OnGETMyFavoritesFurniture(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully);
	void OnGETFurnitureImage(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully);
	
	UPROPERTY()
	class AMyRoomGameModeBase* RoomGM;

	FString localhost = "http://192.168.0.80:8181";
};
