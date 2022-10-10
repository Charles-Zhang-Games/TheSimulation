// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TheSimulationSaveGame.h"
#include "TheSimulationGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UTheSimulationGameInstance final : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int CurrentGameLevel;
	
	UFUNCTION()
	int GetPlayerLevel() const;

	UFUNCTION()
	void SetPlayerLevel(const int Level) const;

public:
	const int AvailableLevels = 3;

private:
	UFUNCTION()
	UTheSimulationSaveGame* InitializeAndLoadSaveGame() const;

	UFUNCTION()
	void SaveGame(UTheSimulationSaveGame* SaveGame) const;

private:
	UPROPERTY()
	FString SaveGameSlot = TEXT("Default");
};
