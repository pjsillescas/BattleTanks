// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	// Move the barrel right amount this frame

	// Given max elevation speed and the frame time
	UE_LOG(LogTemp,Warning,TEXT("Elevating %f"),DegreesPerSecond);
}