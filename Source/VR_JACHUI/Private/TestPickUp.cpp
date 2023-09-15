// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPickUp.h"
#include <Components/BoxComponent.h>
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

ATestPickUp::ATestPickUp()
{

	PrimaryActorTick.bCanEverTick = true;

	boxcomp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxcomp"));
	SetRootComponent(boxcomp);
	boxcomp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//boxcomp->SetCollisionProfileName(FName("PickUp"));
	boxcomp->SetSimulatePhysics(true);
	boxcomp->SetEnableGravity(true);

	meshcomp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshcomp"));
	meshcomp->SetupAttachment(RootComponent);
	meshcomp->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}


void ATestPickUp::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATestPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestPickUp::Grabbed(USkeletalMeshComponent* handMesh)
{
	meshcomp->SetSimulatePhysics(false);
	AttachToComponent(handMesh, FAttachmentTransformRules::KeepWorldTransform);
}

