// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"



void UTankTurret::Rotate(float Throttle) {
	Throttle = FMath::Clamp<float>(Throttle, -1.f, +1.f);
	auto RotationChange = Throttle * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}
