// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Wheel;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPhysicsConstraintComponent* PhysicsConstraint;

	void SetupConstraint();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
