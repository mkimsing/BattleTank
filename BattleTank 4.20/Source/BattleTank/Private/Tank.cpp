// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/Controller.h"
#include "TankTrack.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnTankDeath.Broadcast();
	}
	
	OnTakeDamage.Broadcast();
	return (float)DamageToApply;
}

int32 ATank::GetCurrentHealth() const
{
	return CurrentHealth;
}

void ATank::SetCurrentHealth( int32 HealthValue)
{
	CurrentHealth = HealthValue;
}

int32 ATank::GetMaxHealth() const
{
	return MaxHealth;
}

float ATank::GetHealthPercentage() const
{
	return (float)CurrentHealth / (float)MaxHealth;
}

void ATank::AttemptDilateTime()
{
	if (TimeDilationMeter > 0 && TimeDilated == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.5f);
		TimeDilated = true;
		TimeDilationEvent.Broadcast();
	}
}

void ATank::ResumeTime()
{
	if (TimeDilated == true) {
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
		TimeDilated = false;
		TimeDilationEvent.Broadcast();
	}
}

float ATank::GetTimeDilationMeterPercent()
{
	return TimeDilationMeter / TimeDilationMeterMax;
}

void ATank::ManageDilationMeter()
{
	if (TimeDilated)
	{
		if (TimeDilationMeter > 0)
		{
			TimeDilationMeter -= TDMeterDrainRate;
		}
		else // Out of meter
		{
			ResumeTime();
			TimeDilated = false;
			TimeDilationEvent.Broadcast();
		}
	}
	else
	{
		if (TimeDilationMeter < TimeDilationMeterMax)
		{
			TimeDilationMeter += TDMeterGainRate;
		}
	}
}

/** BOOST IMPLEMENTATION **/
float ATank::GetBoostMeterPercent()
{
	return BoostMeter / BoostMeterMax;
}

void ATank::StartBoost()
{
	GetWorld()->GetTimerManager().SetTimer(BoostTimer, this, &ATank::AttemptBoost, BoostInterval, true,0.0f);
}

void ATank::AttemptBoost()
{
	if (BoostMeter > BoostMeterDrainAmount)
	{
		TArray<UTankTrack*> Tracks;
		GetComponents<UTankTrack>(Tracks);

		if (!Tracks.IsValidIndex(0) || !Tracks.IsValidIndex(1)) { return; }
		Tracks[0]->BoostOnGround(BoostForce);
		Tracks[1]->BoostOnGround(BoostForce);
	}
}
void ATank::StopBoost()
{	
	GetWorld()->GetTimerManager().ClearTimer(BoostTimer);
	
}
void ATank::ManageBoostMeter()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(BoostTimer) && BoostMeter > 0)
	{

		BoostMeter -= BoostMeterDrainAmount;
	}
	else if (GetWorld()->GetTimerManager().IsTimerActive(BoostTimer) && BoostMeter <= 0)
	{
		StopBoost();
	}
	else 
	{
		if (BoostMeter < BoostMeterMax)
		{
			BoostMeter += BoostMeterGainRate;
		}
	}
	
}

