// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "TankAimingComponent.generated.h"

/// Enum representing aiming status
UENUM()
enum class EFiringStatus : uint8
{
	Aiming,
	Locked,
	Firing,
	Reloading,
	OutOfAmmo
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

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Reload();

	//Initialize references to the tank parts
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitTurretComponents(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable)
	int32 GetAmmoCount();

	UFUNCTION(BlueprintCallable)
	int32 GetMaxAmmo();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitAudioComponents(UAudioComponent* ReloadComponentToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	void BeginPlay() override;

private:
	
	bool IsBarrelMoving();
	float Tolerance = 0.01;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel* TankBarrel = nullptr;
	UTankTurret* TankTurret = nullptr;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 6000;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	float LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 MaxAmmo = 4;

	int32 AmmoCount; 		//TODO Reset AmmoCount to Max somewhere

	UFUNCTION()
	void RefillAmmo();

	//Manage the reload timer
	FTimerHandle ReloadTimerHandle;

	/* SOUNDS */
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* FiringSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	UAudioComponent* ReloadSoundComponent = nullptr;
};
