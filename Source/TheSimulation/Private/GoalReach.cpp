// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalReach.h"

#include "TheSimulationGameInstance.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGoalReach::AGoalReach()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Display Mesh");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GoalReachMesh(TEXT("StaticMesh'/Game/Meshes/GoalReach.GoalReach'"));
	if (GoalReachMesh.Succeeded())
		Mesh->SetStaticMesh(GoalReachMesh.Object);
	SetRootComponent(Mesh);
	
	TouchTrigger = CreateDefaultSubobject<UBoxComponent>("Touch Trigger");
	TouchTrigger->InitBoxExtent(FVector(120, 120, 180)); // Looks like this parameter is half-size
	TouchTrigger->SetRelativeLocation(FVector(0,0,100));
	TouchTrigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	TouchTrigger->SetupAttachment(Mesh);
	TouchTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGoalReach::BeginOverlap);

	static ConstructorHelpers::FObjectFinder<USoundWave> GoalMusicSound(TEXT("SoundWave'/Game/Audios/Goal.Goal'"));
	GoalMusic = CreateDefaultSubobject<UAudioComponent>("Goal Music");
	GoalMusic->SetupAttachment(Mesh);
	if (GoalMusicSound.Succeeded())
	{
		GoalMusic->SetSound(GoalMusicSound.Object);
		GoalMusic->bAllowSpatialization = true;
		GoalMusic->bOverrideAttenuation = true;
		auto AttenuationSettings = FSoundAttenuationSettings();
		
		GoalMusic->AttenuationOverrides = AttenuationSettings;
		GoalMusic->SetAutoActivate(true);
	}
}

// Called when the game starts or when spawned
void AGoalReach::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGoalReach::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	const float RunningTime = GetGameTimeSinceCreation();
	const float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	const float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

void AGoalReach::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		UTheSimulationGameInstance* GameInstance = Cast<UTheSimulationGameInstance>(
			UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstance->UnlockLevel(UnlockLevel);
		GetWorld()->ServerTravel("0_MenuMap");	
	}
}