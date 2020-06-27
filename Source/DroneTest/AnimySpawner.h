// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animy.h"
#include <Engine/EngineTypes.h>
#include "AnimySpawner.generated.h"

UCLASS()
class DRONETEST_API AAnimySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimySpawner();

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* SpawnScope;

	UPROPERTY()
	FTimerHandle TimeHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTimeSlot = 2.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAnimy> Animy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnAnimy();

};
