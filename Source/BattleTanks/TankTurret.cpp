// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

#include "Runtime/Engine/Classes/Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move the barrel right amount this frame

	// Given max elevation speed and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewAzimuth = RelativeRotation.Yaw + AzimuthChange;
	auto ClampedAzimuth = FMath::Clamp<float>(RawNewAzimuth, MinAzimuth, MaxAzimuth);

	SetRelativeRotation(FRotator(0, ClampedAzimuth, 0));

	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Move to azimuth %.f"), Time, ClampedAzimuth);

}