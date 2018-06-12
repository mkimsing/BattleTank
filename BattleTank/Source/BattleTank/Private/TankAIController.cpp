// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank =  (GetPawn());

	if (!ensure(PlayerTank) || !ensure(ControlledTank)) { return; }
	
	//Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim towards player
	auto PlayerLocation = PlayerTank->GetActorLocation();
	AimingComponent->AimAt(PlayerLocation);

	//Fire
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
		AimingComponent->Fire();
	}
	
}

void ATankAIController::BeginPlay() {
	
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}
