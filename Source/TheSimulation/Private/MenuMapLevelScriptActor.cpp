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
	for (auto& id: GameInstance->GetUnlockedLevels())
	{
		const int i = id - 1;
		
		const float Radius = IncrementalCircleRadius * (i / 8 + 1);
		const float Angle = (float) i / 8 * (2 * PI);
		
		FVector Position(  -FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, FloorHeight);
		FRotator Rotation(0, -Angle / PI * 180, 0);
		AMenuDoorway* Doorway = Cast<AMenuDoorway>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), AMenuDoorway::StaticClass(), FTransform(Rotation, Position)));
		FText Name = FText::FromString(FString::Printf(TEXT("Level %d"), i + 1));
		Doorway->SetupDoorway(Name);
		Doorway->FinishSpawning(FTransform(Rotation, Position));
	}

	// Generate lighting
	const APointLight* PointLight = GetWorld()->SpawnActor<APointLight>(FVector(0, 0, 900), FRotator(0,0,0));
	PointLight->PointLightComponent->SetIntensity(8);
	PointLight->PointLightComponent->SetIntensityUnits(ELightUnits::Candelas);
	PointLight->PointLightComponent->SetLightColor(FColor(193, 241,255, 55));

	// Play welcome instructions
	MessageID = 0;
	GetWorldTimerManager().SetTimer(SoundPlayDelayHandle, this, &AMenuMapLevelScriptActor::PlayWelcomeMessage, 3, false);
}

void AMenuMapLevelScriptActor::PlayWelcomeMessage()
{
	switch (MessageID)
	{
	case 0:
		UGameplayStatics::PlaySound2D(GetWorld(), LoadObject<USoundWave>(NULL, TEXT("SoundWave'/Game/Audios/0_Welcome_to_The_Simulation.0_Welcome_to_The_Simulation'")));
		
		MessageID = 1;
		GetWorldTimerManager().SetTimer(SoundPlayDelayHandle, this, &AMenuMapLevelScriptActor::PlayWelcomeMessage, 60, false);
		break;
	case 1:
		if (UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation().Length() > 15000)
			UGameplayStatics::PlaySound2D(GetWorld(), LoadObject<USoundWave>(NULL, TEXT("SoundWave'/Game/Audios/0_You_Are_Going_Too_Far.0_You_Are_Going_Too_Far'")));
		break;
	default:
		return;
	}
}


