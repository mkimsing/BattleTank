// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank =  (GetPawn());

	if (!ControlledTank)
	{
		Destroy();
		return;
	}
	if (!PlayerTank) { return; }
	
	DistanceAway = ControlledTank->GetDistanceTo(PlayerTank);
	//Move towards the player
	if (DistanceAway <= ChaseRadius) {
		MoveToActor(PlayerTank, AcceptanceRadius);
	}
	//Aim towards player
	auto PlayerLocation = PlayerTank->GetActorLocation();
	AimingComponent->AimAt(PlayerLocation);
	
	//Fire
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
		if (DistanceAway <= FiringRadius && !GetWorld()->GetTimerManager().IsTimerActive(AIFiringTimer))
		{
			AimingComponent->Fire();

			//Set Timer to limit firing rate
			GetWorld()->GetTimerManager().SetTimer(AIFiringTimer, FiringRate, false, 0.f);

			//Reload if needed
			if (AimingComponent->GetAmmoCount() <= 0
				&& AimingComponent->GetFiringStatus() != EFiringStatus::Reloading)
			{
				AimingComponent->Reload();
			}
		}
	}	
}

void ATankAIController::BeginPlay() {
	
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }
		AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

		//Subscribe OnPossessedTankDeath to the tank's death event
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	OnKilled();
	GetPawn()->DetachFromControllerPendingDestroy();
}