// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
	void AimAt(FVector WorldSpaceAim,float LaunchSpeed);
	
	void SetTurretReference(UStaticMeshComponent* NewTurret);

	void SetBarrelReference(class UTankBarrel* NewBarrel);

	void MoveBarrelTowards(const FVector& AimDirection);
private:
	class UTankBarrel* Barrel;
	class UStaticMeshComponent* Turret;
};
