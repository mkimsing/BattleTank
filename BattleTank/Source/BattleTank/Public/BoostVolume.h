// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BoostVolume.generated.h"
/**
 * 
 */
UCLASS()
class BATTLETANK_API ABoostVolume : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ABoostVolume();

	UFUNCTION()
	void TriggerBoost(AActor* OverlappedActor);

private:
	
	ATriggerBox* Box;
	FTimerHandle BoostTimer;
	float BoostDuration = 1.5f;

	void Boost(AActor* OverlappedActor);

};
