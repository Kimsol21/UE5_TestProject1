// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay(); // 상위 클래스에 구현되어 있는 기본적인 동작들을 먼저 실행해주기 위함. 

	// 마우스를 게임 화면에 포커싱.
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

}
