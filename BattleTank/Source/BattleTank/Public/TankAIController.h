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
	float AcceptanceRadius = 4000;

private:
	void Tick(float DeltaTime) override;

	// Local ref to aiming component
	UTankAimingComponent* AimingComponent;

	virtual void SetPawn(APawn* InPawn) override;
	
	UFUNCTION()
	void OnPossessedTankDeath();
};
