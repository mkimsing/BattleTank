// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  TankTrack is used to set maximum driving force and apply force to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle (float Throttle);
	
	/// Maximum driving force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxDrivingForce = 40000000; // Assuming 1g accel, 40ton tank

private:
	void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewaysForce();

	float CurrentThrottle = 0;

	void DriveTrack();
};
