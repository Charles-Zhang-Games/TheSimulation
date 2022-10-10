// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/TriggerBox.h"
#include "Level2.generated.h"

/**
 * 
 */
UCLASS()
class ALevel2 : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	FActorDataLayer TemplateLayer;

	UPROPERTY(EditAnywhere)
	FActorDataLayer NewWorldLayer;

private:
	UFUNCTION(BlueprintCallable)
	void SwitchWorldLayer(int Index);
	
	UFUNCTION()
	void TriggerBeginOverlap(AActor* Actor, AActor* OtherActor);
};
