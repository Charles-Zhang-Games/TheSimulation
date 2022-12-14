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
	const UTheSimulationGameInstance* GameInstance = Cast<UTheSimulationGameInstance>(
		UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (GameInstance->CurrentGameLevel == 2)
	{
		GameInstance->SetLevel2Attempts(GameInstance->GetLevel2Attempts() + 1);
		if (GameInstance->GetLevel2Attempts() == 3)
			GameInstance->UnlockLevel(5);
	}

	// Super::FellOutOfWorld(dmgType); // Don't perform default behavior
	
	// Play death scream then change map
	USoundWave* Sound = LoadObject<USoundWave>(NULL, TEXT("SoundWave'/Game/Audios/DeathScream.DeathScream'"));
	UGameplayStatics::PlaySound2D(GetWorld(), Sound);
	GetWorldTimerManager().SetTimer(SoundPlayDelayHandle, this, &ABaseCharacter::PlayDeathShout, 2, false);

	// Adjust killz so we can finish playback
	GetWorld()->GetWorldSettings()->KillZ = GetWorld()->GetWorldSettings()->KillZ - 10000; 
}

void ABaseCharacter::PlayDeathShout() const
{
	GetWorld()->ServerTravel("0_MenuMap");
}