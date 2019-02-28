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
	if (World != nullptr)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController != nullptr)
		{
			APawn* PlayerPawn = PlayerController->GetPawn();
			if(PlayerPawn != nullptr)
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

	if (ControlledTank == nullptr) return;
	if (PlayerTank == nullptr) return;

	// TODO Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim at player's location
	FVector HitLocation = PlayerTank->GetActorLocation();
	ControlledTank->AimAt(HitLocation);
	
	// Fire if ready
	ControlledTank->Fire();
}