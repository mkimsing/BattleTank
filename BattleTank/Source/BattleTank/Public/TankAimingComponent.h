// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"

/// Enum representing aiming status
UENUM()
enum class EFiringStatus : uint8
{
	Aiming,
	Locked,
	Reloading
};

/// Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

/// Holds the properties of the barrel and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Aim
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	//Initialize references to the tank parts
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitTurretComponents(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:

	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel* TankBarrel = nullptr;
	UTankTurret* TankTurret = nullptr;

	/// Variables for firing method
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 6000;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	float LastFireTime = 0;
};
