// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

#include "TankAimingComponent.h"
#include "Tank.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (ensure(AimingComponent))
		FoundAimingComponent(AimingComponent);
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Player controller can't find aiming component at Begin Play"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Aim towards crosshair
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	APawn* ControlledTank = GetPawn();

	if (!ensure(ControlledTank)) return;

	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation)
	{
		//ControlledTank->AimAt(HitLocation);
		ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
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
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + MaxSightDistance * LookDirection;
	
	FHitResult Hit;
	bool isHit = GetWorld()->LineTraceSingleByChannel(OUT Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Camera);
	HitLocation = (isHit) ? Hit.Location : FVector::ZeroVector;
	
	return isHit;
}

void ATankPlayerController::SetPawn(class APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		// Subscribe to the tank death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("On death called (Player controller)!!"));
	StartSpectatingOnly();
}