// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Name = GetOwner()->GetName();
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: %s Move Forward (%f)."),Time, *Name,Throw);
}
