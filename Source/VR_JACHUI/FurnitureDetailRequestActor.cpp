// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureDetailRequestActor.h"
#include "HttpModule.h"
#include "JsonParseLibrary.h"
#include "ShowRoomGameModeBase.h"

// Sets default values
AFurnitureDetailRequestActor::AFurnitureDetailRequestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFurnitureDetailRequestActor::BeginPlay()
{
	Super::BeginPlay();
	
	showRoomGM = GetWorld()->GetAuthGameMode<AShowRoomGameModeBase>();
}

// Called every frame
void AFurnitureDetailRequestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFurnitureDetailRequestActor::GETFurnitureInfo(FString UUID)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	FString url = "http://192.168.0.80:8181/api/furniture/detail/";
	url.Append(FString::Printf(TEXT("%s"), *UUID));

	// GETó�� 
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->OnProcessRequestComplete().BindUObject(this, &AFurnitureDetailRequestActor::OnGETFunrintureInfo);
	Request->ProcessRequest();
}

void AFurnitureDetailRequestActor::OnGETFunrintureInfo(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG(LogTemp, Warning, TEXT("GET Furnitures Info"));
		
		// Response �� Parsing
		FString res = Response->GetContentAsString();
		TArray<FFurnitureJsonType> parsedData = UJsonParseLibrary::FavJsonParse(res);
		
		// GameInstance�� ���� UI�� ��Ÿ���� �Ѵ�. 
		// gm2->SetPRText(parsedData);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't GET Furniture Info"));
	}
}

