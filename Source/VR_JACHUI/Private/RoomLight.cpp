// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomLight.h"
#include <UMG/Public/Components/Button.h>
#include "VRCharacter.h"

void URoomLight::NativeConstruct()
{
	Super::NativeConstruct();

	btn_ON->OnClicked.AddDynamic(this, &URoomLight::LightOn);
	btn_OFF->OnClicked.AddDynamic(this, &URoomLight::LightOff);
	btn_class1->OnClicked.AddDynamic(this, &URoomLight::ChangeClass1);
	btn_class2->OnClicked.AddDynamic(this, &URoomLight::ChangeClass2);
	btn_class3->OnClicked.AddDynamic(this, &URoomLight::ChangeClass3);
	btn_Exit->OnClicked.AddDynamic(this, &URoomLight::ExitLightUI);
}

void URoomLight::LightOn()
{

}

void URoomLight::LightOff()
{

}

void URoomLight::ChangeClass1()
{

}

void URoomLight::ChangeClass2()
{

}

void URoomLight::ChangeClass3()
{

}

void URoomLight::ExitLightUI()
{

}