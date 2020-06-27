// Fill out your copyright notice in the Description page of Project Settings.


#include "Animy.h"
#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AAnimy::AAnimy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetGenerateOverlapEvents(true);
	this->OnDestroyed.AddDynamic(this, &AAnimy::DestoryHandler);
}

// Called when the game starts or when spawned
void AAnimy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnimy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->AddActorWorldOffset(FVector(0.0f, 0.0f, 1.0f) * UpRate * DeltaTime);
}

void AAnimy::DestoryHandler(AActor* destoryActor)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeParticle, this->GetActorTransform());
}

