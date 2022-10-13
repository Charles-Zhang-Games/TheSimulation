// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Sound/AmbientSound.h"
#include "MenuMapLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class AMenuMapLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void BeginPlay() override;

private:
	int MessageID;
	FTimerHandle SoundPlayDelayHandle;
	void PlayWelcomeMessage();
};
