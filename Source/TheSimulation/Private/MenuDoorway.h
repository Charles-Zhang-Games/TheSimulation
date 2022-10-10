// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "MenuDoorway.generated.h"

UCLASS()
class AMenuDoorway : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMenuDoorway();

	UPROPERTY()
	UTextRenderComponent* LevelText;

	UPROPERTY()
	UStaticMeshComponent* DoorwayMesh;

	UPROPERTY()
	UBoxComponent* TouchTrigger;

	UFUNCTION()
	void SetupDoorway(FText& Name);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:	
	UPROPERTY()
	FText LevelName;

	UPROPERTY()
	FTransform Transform;
};
