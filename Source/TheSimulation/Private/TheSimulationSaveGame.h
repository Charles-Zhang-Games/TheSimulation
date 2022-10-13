// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TheSimulationSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UTheSimulationSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UTheSimulationSaveGame();
	
	UPROPERTY()
	TSet<int> UnlockedLevels;
};
