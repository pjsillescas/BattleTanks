// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel right amount this frame

	// Given max elevation speed and the frame time
	UWorld* World = GetWorld();
	auto Time = World->GetTimeSeconds();
	UE_LOG(LogTemp,Warning,TEXT("%f: Elevating %f"),Time,RelativeSpeed);
}