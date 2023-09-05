// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// Struct�� ���� ����� ������ �����Ѵ�.
USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FString userId = TEXT("");
	FString userName = TEXT("");

	// �α����� ������ �� Set�� ���Ͽ� userInfo�� �ʱ�ȭ���ش�. 
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
