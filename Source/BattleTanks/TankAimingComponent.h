// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus: uint8
{
	Locked,Aiming,Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	float LaunchSpeed;

	virtual void BeginPlay() override;

	EFiringStatus GetFiringStatus() const;

	virtual void TickComponent(float DeltaTime,enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector WorldSpaceAim);
	
	void SetBarrelReference(class UTankBarrel* NewBarrel);
	void SetTurretReference(class UTankTurret* NewTurret);

	UFUNCTION(BlueprintCallable,Category = "Setup")
	void Initialize(class UTankBarrel* NewBarrel, class UTankTurret* NewTurret);

	void MoveBarrelTowards(const FVector& AimDirection);
	void MoveTurretTowards(const FVector& AimDirection);
	
	UPROPERTY(BlueprintReadOnly,Category = "State")
	EFiringStatus FiringStatus;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable,Category = "Firing")
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ReloadTimeInSeconds;
	double LastFireTime;

private:
	class UTankBarrel* Barrel;
	class UTankTurret* Turret;
	
	FVector AimDirection;
	bool IsBarrelMoving();
};
