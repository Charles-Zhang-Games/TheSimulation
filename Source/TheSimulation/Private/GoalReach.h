// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GoalReach.generated.h"

UCLASS()
class THESIMULATION_API AGoalReach : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGoalReach();

	UPROPERTY(EditAnywhere)
	int UnlockLevel = 1;

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	UBoxComponent* TouchTrigger;

	UPROPERTY()
	UAudioComponent* GoalMusic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
