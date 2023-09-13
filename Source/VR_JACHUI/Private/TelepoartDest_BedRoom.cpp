// Fill out your copyright notice in the Description page of Project Settings.


#include "TelepoartDest_BedRoom.h"
#include <Components/BoxComponent.h>

// Sets default values
ATelepoartDest_BedRoom::ATelepoartDest_BedRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
}

// Called when the game starts or when spawned
void ATelepoartDest_BedRoom::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this,&ATelepoartDest_BedRoom::OnComponentBeginOverlap);
}

// Called every frame
void ATelepoartDest_BedRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATelepoartDest_BedRoom::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

