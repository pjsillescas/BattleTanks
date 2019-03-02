// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UTankAimingComponent* TankAimingComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UTankMovementComponent* TankMovementComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Firing")
	float LaunchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ReloadTimeInSeconds;
	double LastFireTime;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable,Category = "Actions")
	void Fire();

};
