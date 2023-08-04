// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ABAnimNotify_AttackHitCheck.h"
#include "Character/ABAnimationAttackInterface.h"

void UABAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		if (IABAnimationAttackInterface* AttackInterface = Cast<IABAnimationAttackInterface>(MeshComp->GetOwner()))
		{
			AttackInterface->AttackHitCheck();
		}
	}
}
