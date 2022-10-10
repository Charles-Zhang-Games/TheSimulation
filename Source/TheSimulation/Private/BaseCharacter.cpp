// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	// Super::FellOutOfWorld(dmgType); // Don't perform default behavior
	GetWorld()->ServerTravel("0_MenuMap");
}