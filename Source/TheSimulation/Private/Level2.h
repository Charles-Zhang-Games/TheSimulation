// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/StaticMeshActor.h"
#include "WorldPartition/DataLayer/ActorDataLayer.h"
#include "Level2.generated.h"

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

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<AStaticMeshActor> DifficultPlatform;

private:
	UFUNCTION(BlueprintCallable)
	void SwitchWorldLayer(int Index);
	
	UFUNCTION()
	void TriggerBeginOverlap(AActor* Actor, AActor* OtherActor);
};
