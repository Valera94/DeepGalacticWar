// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/AI_CharBase.h"
#include "Components/AC_Weapon.h"
#include "Core/WorldPlayerState.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include <Components\AC_CharMove.h>

AAI_CharBase::AAI_CharBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UAC_CharMove>(ACharacter::CharacterMovementComponentName))
{
	
	PrimaryActorTick.bCanEverTick = false;

}

void AAI_CharBase::BeginPlay()
{
	Super::BeginPlay();

	GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(GA_Shot, 1, INDEX_NONE, this));
	GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(GA_Reload, 1, INDEX_NONE, this));

	AC_Weapon->Server_CreateWeapon();

}



