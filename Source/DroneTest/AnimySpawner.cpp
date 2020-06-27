// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimySpawner.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AAnimySpawner::AAnimySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnScope = CreateDefaultSubobject<UBoxComponent>(TEXT("Scope"));
	RootComponent = SpawnScope;
	SpawnScope->SetBoxExtent(FVector(5000.0f, 5000.0f, 2.0f));
}

// Called when the game starts or when spawned
void AAnimySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimeHandle, this, &AAnimySpawner::SpawnAnimy, SpawnTimeSlot, true);
}

// Called every frame
void AAnimySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimySpawner::SpawnAnimy()
{
	FVector Ori;
	FVector Ext;
	this->GetActorBounds(false, Ori, Ext);
	FVector SpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(Ori, Ext);
	GetWorld()->SpawnActor<AAnimy>(Animy, SpawnPoint, FRotator().ZeroRotator, FActorSpawnParameters());
}

 