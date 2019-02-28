// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "Movement")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable,Category = "Movement")
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable,Category = "Setup")
	void Initialize(class UTankTrack* NewLeftTrack, class UTankTrack* NewRightTrack);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private:
	class UTankTrack* LeftTrack = nullptr;
	class UTankTrack* RightTrack = nullptr;
	
};
