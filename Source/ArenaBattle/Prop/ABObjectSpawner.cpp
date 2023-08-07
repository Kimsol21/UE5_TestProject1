// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/ABObjectSpawner.h"
#include "Character/ABCharacterBase.h"
#include "Game/ABGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AABObjectSpawner::AABObjectSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AABObjectSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnActorInRandPos();
	
}


void AABObjectSpawner::SpawnActorInRandPos()
{
	while (SpawnedActorStorageArray.Num() < NumToSpawn)
	{
		FActorSpawnParameters SpawnParams;
		FRotator SpawnRotator;
		FVector SpawnLocation;

		if (0 == RandomRangeHeight || 0 == RandomRangeWidth) return;

		SpawnLocation.X = rand() % RandomRangeHeight;
		SpawnLocation.Y = rand() % RandomRangeWidth;

		auto ActorToSpawn = GetWorld()->SpawnActor<AABCharacterBase>(AABCharacterBase::StaticClass(), SpawnLocation, SpawnRotator, SpawnParams);
		ActorToSpawn->OnCharacterDeadEvent.AddLambda([this](AABCharacterBase* ActorToRemove)->void {
			SpawnedActorStorageArray.Remove(ActorToRemove);
			auto MyGameMode = Cast<AABGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			MyGameMode->IncreaseKillNum(1);
			SpawnActorInRandPos();
			});
		SpawnedActorStorageArray.Add(ActorToSpawn);
	}
}

