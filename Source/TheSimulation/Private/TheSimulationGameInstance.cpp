// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSimulationGameInstance.h"

#include "Level2SaveGame.h"
#include "Kismet/GameplayStatics.h"

int UTheSimulationGameInstance::GetPlayerLevel() const
{
	const UTheSimulationSaveGame* const SaveGame = InitializeAndLoadSaveGame<UTheSimulationSaveGame>(UTheSimulationSaveGame::StaticClass(), MainSaveGameSlot);
	return SaveGame->PlayerLevel;
}

void UTheSimulationGameInstance::SetPlayerLevel(const int Level) const
{
	UTheSimulationSaveGame* const Data = InitializeAndLoadSaveGame<UTheSimulationSaveGame>(UTheSimulationSaveGame::StaticClass(), MainSaveGameSlot);
	Data->PlayerLevel = Level;
	SaveGame(Data, MainSaveGameSlot);
}

int UTheSimulationGameInstance::GetLevel2Attempts() const
{
	const ULevel2SaveGame* const SaveGame = InitializeAndLoadSaveGame<ULevel2SaveGame>(ULevel2SaveGame::StaticClass(), Level2SaveGameSlot);
	return SaveGame->NumOfAttempts;
}

void UTheSimulationGameInstance::SetLevel2Attempts(const int Attempts) const
{
	ULevel2SaveGame* const Data = InitializeAndLoadSaveGame<ULevel2SaveGame>(ULevel2SaveGame::StaticClass(), Level2SaveGameSlot);
	Data->NumOfAttempts = Attempts;
	SaveGame(Data, Level2SaveGameSlot);
}

template <class SaveGameType>
SaveGameType* UTheSimulationGameInstance::InitializeAndLoadSaveGame(const TSubclassOf<USaveGame> SaveGameClass, const FString& SlotName) const
{
	if(UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		SaveGameType* SaveGame = Cast<SaveGameType>(
			UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		return SaveGame;
	}
	else
	{
		USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
		UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, 0);
		return Cast<SaveGameType>(SaveGame);
	}
}

template <class SaveGameType>
void UTheSimulationGameInstance::SaveGame(SaveGameType* SaveGame, const FString& SlotName)
{
	UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, 0);
}
