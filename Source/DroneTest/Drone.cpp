// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include <PhysicsEngine/PhysicsThrusterComponent.h>
#include "Kismet/KismetMathLibrary.h"
#include <Components/InputComponent.h>

// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetSimulatePhysics(true);
	//这两句有啥用
	//CollisionBox->BodyInstance.bLockXRotation = true;
	//CollisionBox->BodyInstance.bLockYRotation = true;

	DroneBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DroneBody"));
	DroneBody->SetupAttachment(CollisionBox);

	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));
	
	Paddle1->SetupAttachment(DroneBody, TEXT("Paddle1"));
	Paddle2->SetupAttachment(DroneBody, TEXT("Paddle2"));
	Paddle3->SetupAttachment(DroneBody, TEXT("Paddle3"));
	Paddle4->SetupAttachment(DroneBody, TEXT("Paddle4"));
	Paddles.Add(Paddle1);
	Paddles.Add(Paddle2);
	Paddles.Add(Paddle3);
	Paddles.Add(Paddle4);
	

	UpThurster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThurster"));
	UpThurster->SetupAttachment(CollisionBox); 
	UpThurster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorUpVector()));
	UpThurster->ThrustStrength = 980.0f;
	UpThurster->SetAutoActivate(true);

	ForwardThurster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwardThurster"));
	ForwardThurster->SetupAttachment(CollisionBox);
	ForwardThurster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorForwardVector()));
	ForwardThurster->ThrustStrength = 0.0f;
	ForwardThurster->SetAutoActivate(true); 
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADrone::PaddleRotation()
{
	for (int i = 0; i < Paddles.Num(); ++i) {
		Paddles[i]->AddRelativeRotation(FRotator(.0f, GetWorld()->DeltaTimeSeconds * RotationRate, .0f));
		//Paddles[i]->AddWorldRotation(FRotator(.0f, GetWorld()->DeltaTimeSeconds * RotationRate, .0f));
		//Paddles[i]->AddLocalRotation(FRotator(.0f, GetWorld()->DeltaTimeSeconds * RotationRate, .0f));
	}
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,);
	if (GetInputAxisValue(TEXT("Lift")) == 0) {
		UpThurster->ThrustStrength = 980.f;
	}
	if (GetInputAxisValue(TEXT("Forward")) == 0) {
		ForwardThurster->ThrustStrength = 0.0f;

		if (DroneBody->GetRelativeRotation().Pitch != 0) {
			if (FMath::Abs(DroneBody->GetRelativeRotation().Pitch) <= 2.0f) {
				DroneBody->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			}
			else if (DroneBody->GetRelativeRotation().Pitch > 0) {
				DroneBody->AddRelativeRotation(FRotator(-1.0f, 0.0f, 0.0f));
			}
			else if (DroneBody->GetRelativeRotation().Pitch < 0){
				DroneBody->AddRelativeRotation(FRotator(1.0f, 0.0f, 0.0f));
			}
		}
	}
	PaddleRotation();
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Lift"), this, &ADrone::GiveUpPower);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ADrone::GiveForwardPower);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrone::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADrone::DoFire);
}

void ADrone::GiveUpPower(float Value)
{
	UpThurster->ThrustStrength += Value * UpACC * GetWorld()->DeltaTimeSeconds;
	UpThurster->ThrustStrength = FMath::Clamp(UpThurster->ThrustStrength, -UpMax, UpMax);
}

void ADrone::GiveForwardPower(float Value)
{
	ForwardThurster->ThrustStrength += -Value * ForwardACC * GetWorld()->DeltaTimeSeconds;
	ForwardThurster->ThrustStrength = FMath::Clamp(ForwardThurster->ThrustStrength, -ForwardMax, ForwardMax);
	float pitch = DroneBody->GetRelativeRotation().Pitch;
	if (FMath::Abs(pitch) <= 30.0f) {
		DroneBody->AddRelativeRotation(FRotator((20.0f/(FMath::Abs(pitch) + 10.0f)) * -Value, 0.0f, 0.0f));
	}
}


//旋转物体的新方法
//搞清楚以前的项目是怎么添加旋转的   Blueprint 里面有 use controller Rotation Pitch/Yaw/Roll
//对比一下
void ADrone::Turn(float Value)
{
	CollisionBox->AddTorqueInDegrees(this->GetActorUpVector() * Value * TorqueStrength);
}

void ADrone::DoFire()
{
	FTransform temp = DroneBody->GetSocketTransform(TEXT("Fire"));
	GetWorld()->SpawnActor<AMissile>(Bullet, temp);
}


