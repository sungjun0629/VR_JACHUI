// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFavoriteRequestActor.h"
#include "HttpModule.h"
#include "../JsonParseLibrary.h"
#include "../MyRoomGameModeBase.h"
#include "ImageUtils.h"

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

void AMyFavoriteRequestActor::GETMyFavoritesFurniture(const FString myID, const int32 FurnitureNo)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	FString url = "http://localhost:8181/api/furniture/favorite/";
	url.Append(FString::Printf(TEXT("%s/%d"), *myID, FurnitureNo));

	// GET처리 
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->OnProcessRequestComplete().BindUObject(this, &AMyFavoriteRequestActor::OnGETMyFavoritesFurniture);
	Request->ProcessRequest();
}

void AMyFavoriteRequestActor::GETFurnitureImage(const FString furnitureName)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	FString url = "http://localhost:8181/api/furniture/showImage/";
	url.Append(FString::Printf(TEXT("%s"), *furnitureName));

	UE_LOG(LogTemp,Warning,TEXT("Trying to GetFurniture Image : %s "), *furnitureName);
	// GET처리 
	Request->SetURL(url);
	Request->SetHeader(TEXT("Content-Type"), TEXT("image/jpg"));
	Request->OnProcessRequestComplete().BindUObject(this, &AMyFavoriteRequestActor::OnGETFurnitureImage);
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

void AMyFavoriteRequestActor::OnGETFurnitureImage(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG(LogTemp,Warning,TEXT("SUCCESS TO GET MY FAVORITE FURNITURE IMAGE"));
		TArray<uint8> texBites = Response->GetContent();
		
		UTexture2D* realTex = FImageUtils::ImportBufferAsTexture2D(texBites);
		// GameModeBase에서 위젯의 이미지를 변경시켜준다. 
		RoomGM->SetImageTexture(realTex);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("FAILED TO GET MY FAVORITE FURNITURE IMAGE"));
		
	}
}

