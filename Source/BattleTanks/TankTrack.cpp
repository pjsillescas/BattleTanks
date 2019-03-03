// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent,FVector NormalImpulse,const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("OnHit %s"),*(GetOwner()->GetName()));
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();

	auto Mass = Cast<UMeshComponent>(GetOwner()->GetRootComponent())->GetMass();
	auto CorrectionForce = Mass * CorrectionAcceleration / 2;

	AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);

	auto ForceApplied = GetForwardVector() * Throttle * MaxTrackDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}