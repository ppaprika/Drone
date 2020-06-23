// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

UCLASS()
class DRONETEST_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* DroneBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Paddle1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Paddle2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Paddle3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Paddle4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPhysicsThrusterComponent* UpThurster;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPhysicsThrusterComponent* ForwardThurster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UpACC = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UpMax = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForwardACC = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForwardMax = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TorqueStrength = 500000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationRate = 10.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PaddleRotation();

	TArray<UStaticMeshComponent*> Paddles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void GiveUpPower(float Value);

	UFUNCTION()
	void GiveForwardPower(float Value);

	UFUNCTION()
	void Turn(float Value);

	


};
