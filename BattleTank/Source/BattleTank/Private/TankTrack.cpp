// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankTrack::BeginPlay() 
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

//Event fires when tracks are on the ground
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) 
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce() 
{
	///Work out the required acceleration this frame to correct our slipping 
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectingAccel = -SlippageSpeed / DeltaTime *GetRightVector();

	//Find the required sideways friction
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectingAccel) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	//TODO clamp throttle value so player cannot go over speed
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



