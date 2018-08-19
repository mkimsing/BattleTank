// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward Declarations
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public: 
	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnKilled();

protected:

	//How close the AI tanks can get to the player (in cm)
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 6000;

	//How the player needs to be for the tanks to chase (in cm)
	UPROPERTY(EditAnywhere, Category = "Setup")
	float ChaseRadius = 30000;
private:
	void Tick(float DeltaTime) override;

	// Local ref to aiming component
	UTankAimingComponent* AimingComponent;

	virtual void SetPawn(APawn* InPawn) override;
	
	UFUNCTION()
	void OnPossessedTankDeath();

	//How close the player needs to be for the AI to fire
	UPROPERTY(EditAnywhere, Category = "Setup")
	float FiringRadius = 20000;

	float DistanceAway;

	FTimerHandle AIFiringTimer;
	float FiringRate = 3.0f;
};
