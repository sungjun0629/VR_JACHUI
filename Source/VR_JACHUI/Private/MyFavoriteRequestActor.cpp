// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFavoriteRequestActor.h"
#include "HttpModule.h"
#include "../JsonParseLibrary.h"
#include "../MyRoomGameModeBase.h"

// Sets default values
AMyFavoriteRequestActor::AMyFavoriteRequestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyFavoriteRequestActor::BeginPlay()
{
	Super::BeginPlay();
	
	RoomGM = GetWorld()->GetAuthGameMode<AMyRoomGameModeBase>();
}

// Called every frame
void AMyFavoriteRequestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyFavoriteRequestActor::GETMyFavoritesFurniture(const int32 furnitureNo)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	FString url = "";
	url.Append(FString::Printf(TEXT("%d"), furnitureNo));

	// GET처리 
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->OnProcessRequestComplete().BindUObject(this, &AMyFavoriteRequestActor::OnGETMyFavoritesFurniture);
	Request->ProcessRequest();
}

void AMyFavoriteRequestActor::OnGETMyFavoritesFurniture(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully) 
	{
		UE_LOG(LogTemp,Warning,TEXT("SUCCESS TO GET MY FAVORITE FURNITURE"));
		// Response 값에 대하여 Parsing을 진행한다.
		FString response = Response->GetContentAsString();
		TArray<FFurnitureJsonType> parsedData = UJsonParseLibrary::FavJsonParse(response);

		RoomGM->SetFAVFurnitureList(parsedData);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DISABLE TO GET MY FAVORITE FURNITURE"));
	}
}

