// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABCharacterControlDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABCharacterControlDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UABCharacterControlDataAsset();

	UPROPERTY(EditAnywhere, Category = Pawn)
	uint32 bUseControlRotationYaw : 1;

	UPROPERTY(EditAnywhere, Category = Pawn)
	uint32 bUseControlRotationPitch : 1;

	UPROPERTY(EditAnywhere, Category = Pawn)
	uint32 bUseControlRotationRoll : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	FRotator RotationRate;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bUseControllerDesiredRotation : 1;//서서히 바뀌도록

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bOrientRotationToMovement : 1;//그쪽 방향을 바라보도록





	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;





	//Sprint arm Section
	UPROPERTY(EditAnywhere, Category = SpringArm)
	float TargetArmLength;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	FRotator RelativeRotation;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bUsePawnControlRotation : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bDoCollisionTest: 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritYaw : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritPitch : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritRoll : 1;


	
};
