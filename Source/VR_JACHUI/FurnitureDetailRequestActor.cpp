// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnitureDetailRequestActor.h"
#include "HttpModule.h"
#include "JsonParseLibrary.h"

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
	
}

// Called every frame
void AFurnitureDetailRequestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFurnitureDetailRequestActor::GETFurnitureInfo(int furnitureNo)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	FString url = "";
	url.Append(FString::Printf(TEXT("%d"), furnitureNo));

	// GET처리 
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
		
		// Response 값 Parsing
		FString res = Response->GetContentAsString();
		//TArray<FString> parsedData = UJsonParseLibrary::JsonPRParse(res);
		
		// GameInstance를 통해 UI에 나타나게 한다. 
		// gm2->SetPRText(parsedData);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't GET Furniture Info"));
	}
}

