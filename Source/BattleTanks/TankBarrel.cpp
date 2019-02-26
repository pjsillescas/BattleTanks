// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel right amount this frame

	// Given max elevation speed and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed,-1,1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));

	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Aim to elevation %.f"), Time, ClampedElevation);
}