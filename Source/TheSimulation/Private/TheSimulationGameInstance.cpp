// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSimulationGameInstance.h"

#include "Kismet/GameplayStatics.h"

int UTheSimulationGameInstance::GetPlayerLevel() const
{
	const UTheSimulationSaveGame* const SaveGame = InitializeAndLoadSaveGame();
	return SaveGame->PlayerLevel;
}

void UTheSimulationGameInstance::SetPlayerLevel(const int Level) const
{
	UTheSimulationSaveGame* const Data = InitializeAndLoadSaveGame();
	Data->PlayerLevel = Level;
	SaveGame(Data);
}

UTheSimulationSaveGame* UTheSimulationGameInstance::InitializeAndLoadSaveGame() const
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *SaveGameSlot);
	if(UGameplayStatics::DoesSaveGameExist(SaveGameSlot, 0))
	{
		UTheSimulationSaveGame* SaveGame = Cast<UTheSimulationSaveGame>(
			UGameplayStatics::LoadGameFromSlot(SaveGameSlot, 0));
		return SaveGame;
	}
	else
	{
		USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UTheSimulationSaveGame::StaticClass());
		UGameplayStatics::SaveGameToSlot(SaveGame, SaveGameSlot, 0);
		return Cast<UTheSimulationSaveGame>(SaveGame);
	}
}

void UTheSimulationGameInstance::SaveGame(UTheSimulationSaveGame* SaveGame) const
{
	UGameplayStatics::SaveGameToSlot(SaveGame, SaveGameSlot, 0);
}
