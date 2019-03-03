// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	ATank* PlayerTank = nullptr;
	UWorld* World = GetWorld();
	if (ensure(World))
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (ensure(PlayerController))
		{
			APawn* PlayerPawn = PlayerController->GetPawn();
			if(ensure(PlayerPawn))
				PlayerTank = Cast<ATank>(PlayerPawn);
		}
	}

	return PlayerTank;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = GetPlayerTank();

	if (!ensure(ControlledTank)) return;
	if (!ensure(PlayerTank)) return;

	// TODO Move towards the player
	UE_LOG(LogTemp,Warning,TEXT("To player %f"),AcceptanceRadius);
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim at player's location
	FVector HitLocation = PlayerTank->GetActorLocation();
	ControlledTank->AimAt(HitLocation);
	
	// Fire if ready
	ControlledTank->Fire();
}