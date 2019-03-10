// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));

	SetRootComponent(PhysicsConstraint);

	Axle = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axle"));
	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));

	Wheel->SetupAttachment(Axle);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(NAME_None, 100);
	
	Axle->SetupAttachment(PhysicsConstraint);
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this,&ASprungWheel::OnHit);

	SetupConstraint();
	
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	PhysicsConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PrimaryActorTick.GetActualTickGroup() == TG_PostPhysics)
	{
		TotalForceMagnitude = 0;
	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitude += ForceMagnitude;
}

void ASprungWheel::ApplyForce()
{
	UE_LOG(LogTemp,Warning,TEXT("Force %f"),TotalForceMagnitude);
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitude);
}
