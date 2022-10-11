// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "TheSimulationGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	UTheSimulationGameInstance* GameInstance = Cast<UTheSimulationGameInstance>(
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance->CurrentGameLevel == 2)
		GameInstance->SetLevel2Attempts(GameInstance->GetLevel2Attempts() + 1);
	
	// Super::FellOutOfWorld(dmgType); // Don't perform default behavior
	GetWorld()->ServerTravel("0_MenuMap");
}