// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginRequestActor.h"
#include "HttpModule.h"

// Sets default values
ALoginRequestActor::ALoginRequestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALoginRequestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALoginRequestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALoginRequestActor::POSTVerifyIDRequest(const FString url, const FString id, const FString pw)
{
	// API 형식 
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	// Body->JSON으로. 
	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	FString RequestBody;

	RequestObj->SetStringField("id", *id);
	RequestObj->SetStringField("password", *pw);
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	// API POST 형식 : *URL은 추후 변수로 바꿔주어야 한다.
	Request->SetURL("http://172.16.17.79:8888/api/v1/member/login");
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetContentAsString(RequestBody);
	Request->OnProcessRequestComplete().BindUObject(this, &ALoginRequestActor::OnPostVerifySignIn);
	//gm->Id = id;
	Request->ProcessRequest();

}

void ALoginRequestActor::OnPostVerifySignIn(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Login Failed"));
	}
}

