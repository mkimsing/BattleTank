// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward Declarations
class ATank;

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
	ATank* GetControlledTank() const;
	
	ATank* GetPlayerTank() const;
	
	void Tick(float DeltaTime) override;
};
