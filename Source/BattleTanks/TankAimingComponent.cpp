// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Barrel = nullptr;
	FiringStatus = EFiringStatus::Reloading;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* NewBarrel)
{
	Barrel = NewBarrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* NewTurret)
{
	Turret = NewTurret;
}

void UTankAimingComponent::Initialize(UTankBarrel* NewBarrel, UTankTurret* NewTurret)
{
	SetBarrelReference(NewBarrel);
	SetTurretReference(NewTurret);
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim,float LaunchSpeed)
{
	AActor* Owner = GetOwner();
	if (Owner == nullptr) return;
	if (Barrel == nullptr) return;
	if (Turret == nullptr) return;

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OUT OutLaunchVelocity, StartLocation, WorldSpaceAim, LaunchSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	// Work-out difference between current barrel rotation and AimmDirection
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingComponent::MoveTurretTowards(const FVector& AimDirection)
{
	// Work-out difference between current barrel rotation and AimmDirection
	FRotator BarrelRotation = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	Turret->Rotate(DeltaRotator.Yaw);

}

void UTankAimingComponent::Fire(float LaunchSpeed)
{
	FTransform Transform = Barrel->GetSocketTransform(FName("Projectile"));
	FRotator Rotation = Transform.GetRotation().Rotator();
	FVector Location = Transform.GetLocation() + Transform.GetRotation().GetForwardVector() * 500;
	FActorSpawnParameters SpawnParameters;
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation, SpawnParameters);

	Projectile->LaunchProjectile(LaunchSpeed);

}