// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// 1 is max up movement, -1 max down movement (using MaxDegreesPerSecond)
	void Elevate(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20.f;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 35.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0.0f;
};
