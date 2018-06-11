// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankAimingComponent::InitTurretComponents(UTankBarrel * BarrelToSet, UTankTurret* TurretToSet)
{
	TankTurret = TurretToSet;
	TankBarrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(TankBarrel)) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("FiringLocation"));
	
	bool bFoundAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bFoundAimSolution) // Calculate Launch velocity 
	{ 
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	if (!ensure(TankTurret) || !ensure(TankBarrel)){ return;}

	// Work out the difference between current barrel roation and aim direction

	auto BarrelRotation = TankBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - BarrelRotation;

	//Elevate the barrel
	TankBarrel->Elevate(DeltaRotation.Pitch);

	//Rotate the turret
	if (DeltaRotation.Yaw > -180.f && DeltaRotation.Yaw < 180.f)
	{
		TankTurret->Rotate(DeltaRotation.Yaw);
	}
	else // Avoid going the long-way round
	{
		TankTurret->Rotate(-DeltaRotation.Yaw);
	}
}