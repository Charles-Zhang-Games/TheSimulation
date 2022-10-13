// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuDoorway.h"

#include "TheSimulationGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMenuDoorway::AMenuDoorway()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	LevelText = CreateDefaultSubobject<UTextRenderComponent>("Display Text");
	LevelText->SetupAttachment(RootComponent);
	LevelText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	LevelText->SetRelativeLocation(FVector(0, 0, 250));
	DoorwayMesh = CreateDefaultSubobject<UStaticMeshComponent>("Doorway Mesh");
	DoorwayMesh->SetupAttachment(RootComponent);
	DoorwayMesh->SetRelativeLocation(FVector(-30, -100, 0));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Meshes/Doorway"));
	if (Mesh.Succeeded())
		DoorwayMesh->SetStaticMesh(Mesh.Object);
	TouchTrigger = CreateDefaultSubobject<UBoxComponent>("Touch Trigger");
	TouchTrigger->InitBoxExtent(FVector(40, 60, 100));
	TouchTrigger->SetRelativeLocation(FVector(0, 0, 100));
	TouchTrigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	TouchTrigger->SetupAttachment(RootComponent);
	TouchTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMenuDoorway::BeginOverlap);
	
	SetActorTransform(Transform);
}

void AMenuDoorway::SetupDoorway(FText& Name)
{
	LevelName = Name;
	
	LevelText->SetText(LevelName);
}

// Called when the game starts or when spawned
void AMenuDoorway::BeginPlay()
{
	Super::BeginPlay();
}

void AMenuDoorway::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UTheSimulationGameInstance* const GameInstance = Cast<UTheSimulationGameInstance>(
		UGameplayStatics::GetGameInstance(GetWorld()));
	FString Left, Right;
	LevelName.ToString().Split(" ", &Left, &Right);
	GameInstance->CurrentGameLevel = FCString::Atoi(*Right);

	const FString Name = TEXT("/Game/Maps/") + LevelName.ToString().Replace(TEXT(" "), TEXT(""));
	GetWorld()->ServerTravel(Name);
}
