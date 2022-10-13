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

public:
	UFUNCTION()
	TSet<int> GetUnlockedLevels() const;

	UFUNCTION()
	void UnlockLevel(const int Level) const;

	UFUNCTION()
	int GetLevel2Attempts() const;

	UFUNCTION()
	void SetLevel2Attempts(const int Attempts) const;

private:
	template<class SaveGameType>
	SaveGameType* InitializeAndLoadSaveGame(TSubclassOf<USaveGame> SaveGameClass, const FString& SlotName) const;

	template<class SaveGameType>
	static void SaveGame(SaveGameType* SaveGame, const FString& SlotName);

private:
	const FString MainSaveGameSlot = TEXT("Main");
	const FString Level2SaveGameSlot = TEXT("Level2");
};
