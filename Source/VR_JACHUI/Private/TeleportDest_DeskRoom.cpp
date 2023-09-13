// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportDest_DeskRoom.h"
#include <Components/BoxComponent.h>

// Sets default values
ATeleportDest_DeskRoom::ATeleportDest_DeskRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
}

// Called when the game starts or when spawned
void ATeleportDest_DeskRoom::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ATeleportDest_DeskRoom::OnComponentBeginOverlap);
}

// Called every frame
void ATeleportDest_DeskRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportDest_DeskRoom::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

