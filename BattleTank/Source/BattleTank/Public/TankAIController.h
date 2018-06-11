// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward Declarations
class ATank;
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

private:
	void Tick(float DeltaTime) override;

	//How close the AI tanks can get to the player (in cm)
	float AcceptanceRadius = 4000;

	// Local ref to aiming component
	UTankAimingComponent* AimingComponent;
};
