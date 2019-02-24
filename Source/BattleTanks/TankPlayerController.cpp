// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

#include "Tank.h"

#define OUT

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Aim towards crosshair
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* ControlledTank = GetControlledTank();

	if (ControlledTank == nullptr) return;

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());

		// TODO: Tell controlled tank to aim at this point
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Get camera forward vector

	// Get Crosshair location
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	bool isHit = false;
	// "de-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation,OUT LookDirection))
	{
		// Raycast for a maximum distance
		isHit = GetLookVectorHitLocation(LookDirection,OUT HitLocation);

		/*
		FVector LineTraceEnd = CameraWorldLocation + MaxSightDistance * CameraWorldDirection;

		UE_LOG(LogTemp, Warning, TEXT("Line (%s) %s => %s"), *(CameraWorldDirection.ToString()), *(CameraWorldLocation.ToString()), *(LineTraceEnd.ToString()));

		DrawDebugLine(GetWorld(), CameraWorldLocation, LineTraceEnd, FColor::Red, true, 2, 0, 2);

		FCollisionQueryParams QueryParams(FName(TEXT("")), false, GetOwner());
		FHitResult Hit;
		GetWorld()->LineTraceSingleByObjectType(OUT Hit, CameraWorldLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams);
		isHit = !Hit.ImpactPoint.IsZero();
		HitLocation = (isHit) ? Hit.ImpactPoint : FVector::ZeroVector;
		*/
	}


	return isHit;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation,FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OUT LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection,FVector& HitLocation) const
{
	ATank* Tank = GetControlledTank();
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + MaxSightDistance * LookDirection;
	
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, 1, 0, 2);
	
	FHitResult Hit;
	bool isHit = GetWorld()->LineTraceSingleByChannel(OUT Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
	HitLocation = (isHit) ? Hit.Location : FVector::ZeroVector;
	
	return isHit;
}