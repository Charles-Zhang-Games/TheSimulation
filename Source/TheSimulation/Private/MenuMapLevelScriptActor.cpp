// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuMapLevelScriptActor.h"

#include "MenuDoorway.h"
#include "TheSimulationGameInstance.h"
#include "Components/PointLightComponent.h"
#include "Engine/PointLight.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"

void AMenuMapLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	// Populate gateways
	const UTheSimulationGameInstance* const GameInstance = Cast<UTheSimulationGameInstance>(
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance == nullptr)
		return;

	const float FloorHeight = 400;
	const float IncrementalCircleRadius = 500;
	for (int i = 0; i < FMath::Min(GameInstance->GetPlayerLevel(), GameInstance->AvailableLevels); ++i)
	{
		const float Radius = IncrementalCircleRadius * (i / 8 + 1);
		const float Angle = (float) i / 8 * (2 * PI);
		
		FVector Position(  -FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, FloorHeight);
		FRotator Rotation(0, 0, Angle / PI * 180);
		AMenuDoorway* Doorway = Cast<AMenuDoorway>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), AMenuDoorway::StaticClass(), FTransform(Rotation, Position)));
		FText Name = FText::FromString(FString::Printf(TEXT("Level %d"), i + 1));
		Doorway->SetupDoorway(Name);
		Doorway->FinishSpawning(FTransform(Rotation, Position));
	}

	// Generate lighting
	const APointLight* PointLight = GetWorld()->SpawnActor<APointLight>(FVector(0, 0, 900), FRotator(0,0,0));
	PointLight->PointLightComponent->SetIntensity(8);
	PointLight->PointLightComponent->SetIntensityUnits(ELightUnits::Candelas);

	// Play welcome instructions
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientSound::StaticClass(), Actors);
	if (Actors.Num() == 1)
	{
		PlaybackSound = Cast<AAmbientSound>(Actors[0]);
		
		GetWorldTimerManager().SetTimer(SoundPlayDelayHandle, this, &AMenuMapLevelScriptActor::PlayWelcomeMessage, 5, false);
	}
}

void AMenuMapLevelScriptActor::PlayWelcomeMessage() const
{
	PlaybackSound->Play();
}


