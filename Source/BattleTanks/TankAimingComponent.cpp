// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Barrel = nullptr;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* NewBarrel)
{
	Barrel = NewBarrel;
}

void UTankAimingComponent::SetTurretReference(UStaticMeshComponent* NewTurret)
{
	Turret = NewTurret;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim,float LaunchSpeed)
{
	AActor* Owner = GetOwner();
	if (Owner == nullptr) return;
	if (Barrel == nullptr) return;
	
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OUT OutLaunchVelocity, StartLocation, WorldSpaceAim, LaunchSpeed);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found!!"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found."),Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	// Work-out difference between current barrel rotation and AimmDirection
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	Barrel->Elevate(DeltaRotator.Yaw);

	// Get Roll - Pitch - Yaw Angles

	// Build new rotation

	// Set Roll - Pitch to the turret

	// Set Yaw to the barrel
}