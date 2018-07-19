// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	// Sets default values for this pawn's properties
	ATank();
	
public:
	float TakeDamage( float DamageAmount, struct FDamageEvent const
		& DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(int32 HealthValue);

	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetMaxHealth() const;
	
	UPROPERTY(BlueprintAssignable)
	FTankDelegate OnTankDeath;

	FTankDelegate OnTakeDamage;

	UPROPERTY(BlueprintAssignable, Category = "TimeDilation")
	FTankDelegate TimeDilationEvent;

	void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "TimeDilation")
	void AttemptDilateTime();

	UFUNCTION(BlueprintCallable, Category = "TimeDilation")
	void ResumeTime();

	UFUNCTION(BlueprintCallable, Category = "TimeDilation")
	void ManageDilationMeter();

	UFUNCTION(BlueprintCallable, Category = "TimeDilation")
	float GetTimeDilationMeterPercent();

	UFUNCTION(BlueprintCallable, Category = "Boost")
	void StartBoost();

	UFUNCTION(BlueprintCallable, Category = "Boost")
	void StopBoost();

	UFUNCTION(BlueprintCallable, Category = "Boost")
	void ManageBoostMeter();

	UFUNCTION(BlueprintCallable, Category = "Boost")
	float GetBoostMeterPercent();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 MaxHealth = 60;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	//Time Dilation Implementation
	UPROPERTY(EditDefaultsOnly, Category = "TimeDilation")
	float TimeDilationMeterMax = 100;

	UPROPERTY(VisibleAnywhere, Category = "TimeDilation")
	float TimeDilationMeter = TimeDilationMeterMax;

	UPROPERTY(EditDefaultsOnly, Category = "TimeDilation")
	float TDMeterDrainRate = 0.3;

	UPROPERTY(EditDefaultsOnly, Category = "TimeDilation")
	float TDMeterGainRate = 0.3;

	bool TimeDilated = false;

	// BOOST Implementation

	void AttemptBoost();

	UPROPERTY(EditDefaultsOnly, Category = "Boost")
	float BoostMeterMax = 100;

	UPROPERTY(VisibleAnywhere, Category = "Boost")
	float BoostMeter = BoostMeterMax;

	UPROPERTY(EditDefaultsOnly, Category = "Boost")
	float BoostMeterDrainAmount = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "Boost")
	float BoostMeterGainRate = 0.3;

	UPROPERTY(EditDefaultsOnly, Category = "Boost")
	float BoostInterval = 0.1;

	FTimerHandle BoostTimer;

	float BoostForce = 450000000;
};