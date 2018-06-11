// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank =  Cast<ATank>(GetPawn());

	// If the player has a tank
	if (ensure(PlayerTank))
	{
		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim towards player
		auto PlayerLocation = PlayerTank->GetActorLocation();
		ControlledTank->AimAt(PlayerLocation);

		//Fire
		ControlledTank->Fire();
	}
}

void ATankAIController::BeginPlay() {
	
	Super::BeginPlay();
}
