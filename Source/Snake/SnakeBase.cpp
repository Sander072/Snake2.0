// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.0f;
	MovementSpeed = 0.5f;
	LastMovementDirection = EMovementDirection::DOWN;

}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	AddSnakeElement(4);
	SetActorTickInterval(MovementSpeed);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; i++)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		SnakeElements.Add(NewSnakeElement);
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector = FVector::ZeroVector;
	float MovementSpeed = ElementSize;

	switch (LastMovementDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += MovementSpeed;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= MovementSpeed;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += MovementSpeed;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= MovementSpeed;
		break;
	}

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PreviousElement = SnakeElements[i - 1];

		FVector PreviousLocation = PreviousElement->GetActorLocation();
		CurrentElement->SetActorLocation(PreviousLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
}



