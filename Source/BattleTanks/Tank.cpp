// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "Runtime/Engine/Classes/Engine/World.h"

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("TankAimingComponent"));

	LaunchSpeed = 4000; // TODO Find a sensible default
	Barrel = nullptr;
}

void ATank::SetBarrelReference(UTankBarrel* NewBarrel)
{
	TankAimingComponent->SetBarrelReference(NewBarrel);
	Barrel = NewBarrel;
}

void ATank::SetTurretReference(UTankTurret* NewTurret)
{
	TankAimingComponent->SetTurretReference(NewTurret);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
}

void ATank::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp,Warning,TEXT("%f: Fire!!"),Time);

	if (Barrel == nullptr) return;

	// Spawn a projectile at the socket location on the barrel
	FTransform Transform = Barrel->GetSocketTransform(FName("Projectile"));
	FVector Location = Transform.GetLocation() + Transform.GetRotation().GetForwardVector() * 400;
	FRotator Rotation = Transform.GetRotation().Rotator();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.ObjectFlags = EObjectFlags::RF_Public;
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation, SpawnParameters);
}