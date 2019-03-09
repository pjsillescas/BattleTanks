// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	StartingHealth = 100;
	Health = StartingHealth;
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

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	float DamageToApply = FMath::Clamp<int32>(DamagePoints,0,Health);
	Health -= DamageToApply;

	UE_LOG(LogTemp,Warning,TEXT("Taking damage %i from %i, total health %i"), DamagePoints,Health,Health - DamagePoints);

	if (Health <= 0)
	{
		OnDeath.Broadcast();
		Destroy();
	}

	return DamageToApply;
}


float ATank::getHealthPercent() const
{
	return ((float) Health) / ((float) StartingHealth);
}