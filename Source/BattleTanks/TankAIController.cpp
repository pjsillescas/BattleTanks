// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"

#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
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

	if (!ensure(ControlledTank && PlayerTank)) return;

	// TODO Move towards the player
	//UE_LOG(LogTemp,Warning,TEXT("To player %f"),AcceptanceRadius);
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim at player's location
	FVector HitLocation = PlayerTank->GetActorLocation();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(HitLocation);
	
	// If aim or locked, then fire
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(class APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		// Subscribe to the tank death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp,Warning,TEXT("On death called!!"));
}