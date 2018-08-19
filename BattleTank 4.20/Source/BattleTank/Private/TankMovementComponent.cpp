// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "GameFramework/Actor.h"
#include "TankTrack.h"

void UTankMovementComponent::InitTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);
}

/// Pathfinding logic for the AI tanks
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	//Replacing functionality, no need to call super functionality
	
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); // Current Direction
	auto AIMovementIntent = MoveVelocity.GetSafeNormal(); // Intended Direction

	//Use vector dot product to find Cos(angle) between the two vectors
	// - Cosine result gives throw for forward movement
	auto ForwardThrow = FVector::DotProduct(TankForward, AIMovementIntent);
	IntendMoveForward(ForwardThrow);

	//Use vector cross prodcut to find the Sin(angle) between the two vectors
	// - Sine result gives throw for right/left movement
	FVector RightThrow = FVector::CrossProduct(TankForward, AIMovementIntent);
	IntendTurnRight(RightThrow.Z);
}