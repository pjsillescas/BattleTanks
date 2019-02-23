// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();

	if(Tank != nullptr)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Possesed tank: %s"), *(Tank->GetName()));
	}

	ATank* PlayerTank = GetPlayerTank();

	if (PlayerTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank found: %s"), *(PlayerTank->GetName()));
	}

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
			PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	}

	return PlayerTank;
}
