// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay(); // ���� Ŭ������ �����Ǿ� �ִ� �⺻���� ���۵��� ���� �������ֱ� ����. 

	// ���콺�� ���� ȭ�鿡 ��Ŀ��.
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

}
