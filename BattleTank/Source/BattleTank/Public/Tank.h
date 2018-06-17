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

	FTankDelegate OnTankDeath;
	FTankDelegate OnTakeDamage;

	void BeginPlay();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

};
