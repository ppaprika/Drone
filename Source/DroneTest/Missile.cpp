// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Animy.h"
#include "DroneTestGameModeBase.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	RootComponent = Mesh;

	Movement->InitialSpeed = 5000;
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMissile::ShotTarget);
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMissile::ShotTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AAnimy>()) {
		OtherActor->Destroy();
		//cast 转换以后得到的是指针
		ADroneTestGameModeBase* temp = Cast<ADroneTestGameModeBase>(GetWorld()->GetAuthGameMode());
		if (temp) {
			temp->scores += 1;
		}
		this->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("hit"));
	}
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

