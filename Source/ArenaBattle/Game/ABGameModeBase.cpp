// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameModeBase.h"

const uint8 AABGameModeBase::GOAL_OF_KILL(5);

AABGameModeBase::AABGameModeBase()
{
	//Init Member Variable
	TotalKillNum = 0;


	//Load & Apply Class Info
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/ArenaBattle/Character/BP_Player.BP_Player_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ArenaBattle.ABPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

void AABGameModeBase::IncreaseKillNum(uint8 _NewKill)
{
	TotalKillNum += _NewKill;

	if (GOAL_OF_KILL <= TotalKillNum)
	{
		KillGameOverEvent.Broadcast();
		UE_LOG(LogTemp, Error, TEXT("Game Clear!!@@@@@@@@@@@@@@@@@"));
	}
}
