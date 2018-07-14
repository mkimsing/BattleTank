// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankTrack::BeginPlay() 
{
	Super::BeginPlay();
}

void UTankTrack::SetThrottle(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	float ForceApplied = 0;
	if (FPlatformTime::Seconds() - LastBoostTime < BoostDuration)
	{
		ForceApplied = CurrentThrottle * (MaxDrivingForce + BoostForce);
	}
	else {
		ForceApplied = CurrentThrottle * MaxDrivingForce;
	}
	auto Wheels = GetWheels();

	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{

		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*>ResultArray;
	TArray<USceneComponent*>Children;

	GetChildrenComponents(true, Children);
	for (USceneComponent*Child : Children) {
		USpawnPoint* SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}

void UTankTrack::Boost()
{
	LastBoostTime = FPlatformTime::Seconds();
}

