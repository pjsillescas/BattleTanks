// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	void DriveTrack(float CurrentThrottle);
public:
	UTankTrack();

	TArray<class ASprungWheel*> GetWheels() const;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable,Category = "Input")
	void SetThrottle(float Throttle);

	// Max force per track in newtons
	UPROPERTY(EditDefaultsOnly,Category = "Custom")
	float MaxTrackDrivingForce = 40000000; // Assuming 40 tonn tank and 1g = 10 m/s
};
