// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

#include "Runtime/Engine/Classes/Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent,FVector NormalImpulse,const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce(GetWorld()->GetDeltaSeconds());

	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce(float DeltaTime)
{
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto Mass = Cast<UMeshComponent>(GetOwner()->GetRootComponent())->GetMass();
	auto CorrectionForce = Mass * CorrectionAcceleration / 2;

	AddForce(CorrectionForce);

}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);

	DriveTrack();
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxTrackDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}