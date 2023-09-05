// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// Struct를 통해 사용자 정보를 저장한다.
USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FString userId = TEXT("");
	FString userName = TEXT("");

	// 로그인이 성공될 때 Set을 통하여 userInfo를 초기화해준다. 
	FORCEINLINE void Set(FString uID, FString uName) { userId = uID ; userName = uName; }
};

/**
 * 
 */
UCLASS()
class VR_JACHUI_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
};
