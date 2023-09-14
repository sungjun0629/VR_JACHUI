// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "FurnitureDetailRequestActor.generated.h"

UCLASS()
class VR_JACHUI_API AFurnitureDetailRequestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFurnitureDetailRequestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GETFurnitureInfo(FString furnitureUUID);


private:
	void OnGETFunrintureInfo(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully);
	
	UPROPERTY()
	class AShowRoomGameModeBase* showRoomGM;
};
