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

	ABoostVolume();

public:

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float BoostForce = 500000000;
};
