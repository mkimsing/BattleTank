// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();

	AmmoCount = MaxAmmo;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else if (AmmoCount <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::InitTurretComponents(UTankBarrel * BarrelToSet, UTankTurret* TurretToSet)
{
	TankTurret = TurretToSet;
	TankBarrel = BarrelToSet;
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(TankBarrel)) { return false; }

	return !(AimDirection.Equals(TankBarrel->GetForwardVector(), Tolerance));
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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

void UTankAimingComponent::Fire() {

	if (AmmoCount != 0) { // TODO Clean up this logic ?
		if (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming) {
			if (!ensure(TankBarrel)) { return; }
			if (!ensure(ProjectileBlueprint)) { return; }
			//Spawn a projectile at the end of the barrel
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				TankBarrel->GetSocketLocation(FName(TEXT("FiringLocation"))),
				TankBarrel->GetSocketRotation(FName(TEXT("FiringLocation")))
				);

			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
			AmmoCount--;
		}
	}
}

int32 UTankAimingComponent::GetAmmoCount()
{
	return AmmoCount;
}