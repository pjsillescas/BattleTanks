// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Barrel = nullptr;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* NewBarrel)
{
	Barrel = NewBarrel;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	AActor* Owner = GetOwner();
	if (Owner == nullptr) return;
	if (Barrel == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("AimAt ok"));
	
	FVector BarrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *(Owner->GetName()), *(WorldSpaceAim.ToString()),*(BarrelLocation.ToString()));
}
