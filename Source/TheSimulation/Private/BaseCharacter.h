// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class THESIMULATION_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

public:
	virtual void FellOutOfWorld(const UDamageType& dmgType) override;

private:
	FTimerHandle SoundPlayDelayHandle;
	
	UFUNCTION()
	void PlayDeathShout() const;
};
