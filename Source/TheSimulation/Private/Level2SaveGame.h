// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Level2SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ULevel2SaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	int NumOfAttempts = 0;
};
