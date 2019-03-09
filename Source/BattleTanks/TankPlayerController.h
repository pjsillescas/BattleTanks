// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxSightDistance = 1000000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrossHairXLocation = 0.5;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CrossHairYLocation = 1. / 3;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(class UTankAimingComponent* AimingCompRef);

public:

	virtual void BeginPlay() override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetPawn(class APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

};
