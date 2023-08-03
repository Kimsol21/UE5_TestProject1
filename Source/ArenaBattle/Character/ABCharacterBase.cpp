// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "Character/ABCharacterControlDataAsset.h"
#include "Character/ABComboActionData.h"

// Sets default values
AABCharacterBase::AABCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//CharacterControlData
	static ConstructorHelpers::FObjectFinder<UABCharacterControlDataAsset> ShoulderDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlDataAsset'/Game/ArenaBattle/CharacterControl/DA_Shoulder.DA_Shoulder'"));
	if (ShoulderDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UABCharacterControlDataAsset> QuaterDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlDataAsset'/Game/ArenaBattle/CharacterControl/DA_Quater.DA_Quater'"));
	if (QuaterDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
	}

	// �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Ram.SK_CharM_Ram'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	//�ִϸ��̼� ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/ArenaBattle/Animation/ABP_Player.ABP_Player_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	// ��Ÿ�� ����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboAttackAnimMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattle/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboAttackAnimMontageRef.Object)
	{
		ComboActionMontage = ComboAttackAnimMontageRef.Object;
	}



	// ĳ���� ī�޶� ���� ���ð�
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Capsule Component
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// SkeletalMesh Component 
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	// CharacterMovement Component
	GetCharacterMovement()->bOrientRotationToMovement = true; //�̵��Ҷ� ���ʹ������� ȸ���� ��ų�ų�
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);// �ѹ��� �ٲ�� ����
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;//���߿��� �̵��Ҷ��� ��
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;//�̵��ϴٰ� ���⶧ ������ ������� �Ҳ���

	



	

	
	
}

// Called to bind functionality to input
void AABCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AABCharacterBase::SetCharacterContorolData(const UABCharacterControlDataAsset* CharacterControlData)
{

	bUseControllerRotationPitch = CharacterControlData->bUseControlRotationPitch;
	bUseControllerRotationRoll = CharacterControlData->bUseControlRotationRoll;
	bUseControllerRotationYaw = CharacterControlData->bUseControlRotationYaw;

	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement; //�̵��Ҷ� ���ʹ������� ȸ���� ��ų�ų�
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;// �ѹ��� �ٲ�� ����

}

void AABCharacterBase::ProccessComboAttack()
{
	

	if (0 == CurrentCombo)
	{
		ComboActionBegin();
		return;
	}
	

	//���� �Է��� ���Դ���
	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
}

void AABCharacterBase::ComboActionBegin()
{
	CurrentCombo = 1;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	const float AttackSpeedRate = 1.0f;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

	FOnMontageEnded MontageEndDelegate;
	MontageEndDelegate.BindUObject(this, &AABCharacterBase::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(MontageEndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboTimerChecker();
}

void AABCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsEnded)
{
	CurrentCombo = 0;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AABCharacterBase::SetComboTimerChecker()
{
	if (!ComboActionData) return;
	

	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = 1.0f;

	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex]/ComboActionData->FrameRate)/AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AABCharacterBase::ComboCheck, ComboEffectiveTime, false);
	}
}

void AABCharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();

	if (HasNextComboCommand)
	{
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->maxComboCount);

		FName NextSectionName = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionPrefix, CurrentCombo);

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_JumpToSection(NextSectionName, ComboActionMontage);

		SetComboTimerChecker();
		HasNextComboCommand = false;
	}
}

