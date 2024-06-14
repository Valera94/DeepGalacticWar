// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Components/BaseWidgetComponent.h"
#include "Core/Characters/Base_Character.h"
#include "GAS/Attributes/Attribute_Health.h"
#include "AI_CharBase.generated.h"


class UAIPerceptionStimuliSourceComponent;
class UAC_Health;
class UAC_Weapon;


UCLASS(Abstract)
class TESTPROJECT_API AAI_CharBase : public ABase_Character
{
	GENERATED_BODY()

public:


	AAI_CharBase(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)TSubclassOf<UGameplayAbility >GA_Shot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)TSubclassOf<UGameplayAbility >GA_Reload;

};
