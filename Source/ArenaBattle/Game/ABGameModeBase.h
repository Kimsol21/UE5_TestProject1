#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABGameModeBase.generated.h"

DECLARE_EVENT(AABGameModeBase, FKillGameOverEvent)

UCLASS()
class ARENABATTLE_API AABGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AABGameModeBase();

public:
	void IncreaseKillNum(uint8 _NewKill);
	FKillGameOverEvent& KillGameOver() { return KillGameOverEvent; };

private:
	static const uint8 GOAL_OF_KILL; 
	uint8 TotalKillNum;

	FKillGameOverEvent KillGameOverEvent;
};
