// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Name = GetOwner()->GetName();
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: %s Move Forward (%f)."),Time, *Name,Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Initialize(UTankTrack* NewLeftTrack, UTankTrack* NewRightTrack)
{
	if (NewLeftTrack == nullptr || NewRightTrack == nullptr) return;

	LeftTrack = NewLeftTrack;
	RightTrack = NewRightTrack;
}