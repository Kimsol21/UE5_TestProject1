#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABObjectSpawner.generated.h"

UCLASS()
class ARENABATTLE_API AABObjectSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABObjectSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void SpawnActorInRandPos();

	UPROPERTY(EditAnywhere, Category = Spawner)
	uint8 RandomRangeWidth;

	UPROPERTY(EditAnywhere, Category = Spawner)
	uint8 RandomRangeHeight;

	UPROPERTY(EditAnywhere, Category = Spawner)
	uint8 NumToSpawn;

	UPROPERTY(EditAnywhere, Category = Spawner)
	TSubclassOf<AActor> ClassToSpawn;

	UPROPERTY(EditAnywhere, Category = Spawner)
	TArray<class AABCharacterBase*> SpawnedActorStorageArray;
};
