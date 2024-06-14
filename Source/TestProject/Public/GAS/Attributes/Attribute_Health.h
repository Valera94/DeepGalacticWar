// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Attribute_Health.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateCurrentHealth, float, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegateDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegateRespawn);

UCLASS()
class TESTPROJECT_API UAttribute_Health : public UAttributeSet
{
	GENERATED_BODY()
public:

	UFUNCTION() void Respawn(const float SetDefaultHealth);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateCurrentHealth OnDelegateCurrentHealth;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateDie OnDelegateDie;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateRespawn OnDelegateRespawn;

	ATTRIBUTE_ACCESSORS(UAttribute_Health, Health)
	ATTRIBUTE_ACCESSORS(UAttribute_Health, HealthMax)
	ATTRIBUTE_ACCESSORS(UAttribute_Health, Damage)


protected:

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_HealthMax)FGameplayAttributeData HealthMax;
	UPROPERTY(BlueprintReadOnly, Category = "Health")FGameplayAttributeData Damage;

private:

	UAttribute_Health();


	UFUNCTION()virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()virtual void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)  const override;

};