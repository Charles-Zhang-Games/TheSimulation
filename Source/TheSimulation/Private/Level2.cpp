// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "WorldPartition/DataLayer/WorldDataLayers.h"

void ALevel2::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriggerBox::StaticClass(), FoundActors);
	if (FoundActors.Num() == 1)
	{
		ATriggerBox* TriggerBox = Cast<ATriggerBox>(FoundActors[0]);
		TriggerBox->OnActorBeginOverlap.AddDynamic(this, &ALevel2::TriggerBeginOverlap);
	}
}

void ALevel2::SwitchWorldLayer(int Index)
{
	if (Index == 0)
	{
		GetWorld()->GetWorldDataLayers()->SetDataLayerRuntimeState(TemplateLayer, EDataLayerRuntimeState::Activated);
		GetWorld()->GetWorldDataLayers()->SetDataLayerRuntimeState(NewWorldLayer, EDataLayerRuntimeState::Loaded);
	}
	else if (Index == 1)
	{
		GetWorld()->GetWorldDataLayers()->SetDataLayerRuntimeState(TemplateLayer, EDataLayerRuntimeState::Loaded);
		GetWorld()->GetWorldDataLayers()->SetDataLayerRuntimeState(NewWorldLayer, EDataLayerRuntimeState::Activated);
	}
}

void ALevel2::TriggerBeginOverlap(AActor* Actor, AActor* OtherActor)
{
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		const ATriggerBox* TriggerActor = Cast<ATriggerBox>(Actor);
		if (TriggerActor != nullptr)
		{
			const auto TriggerLocation = TriggerActor->GetActorLocation();
			const auto PawnLocation = OtherActor->GetActorLocation();
			if (TriggerLocation.Z > PawnLocation.Z)
				SwitchWorldLayer(0);
			else
				SwitchWorldLayer(1);
		}
	}
}
