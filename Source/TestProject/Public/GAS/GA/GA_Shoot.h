// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GAS/GA_GameplayAbility.h"
#include "GA_Shoot.generated.h"


USTRUCT(BlueprintType)
struct FGameplayAbilityTargetDataHandle_Custom : public FGameplayAbilityTargetDataHandle
{
	GENERATED_BODY()

	//UFUNCTION(BlueprintCallable,BlueprintPure) FHitResult GetHitResult(){return this->GetHitResult()}
};

UCLASS(Abstract)
class TESTPROJECT_API UGA_Shoot : public UGA_GameplayAbility
{
	GENERATED_BODY()

public:

	UGA_Shoot();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) FGameplayTag ActivateGameplayCueTag;

	UFUNCTION(BlueprintCallable) void Shoot();
	void StartRangedWeaponTargeting();

	UFUNCTION(Server, Unreliable)void Server_OnRangedWeaponTargetDataReady(const bool ActivateTraceFromServer,
		const FVector TraceEnd, const FVector TraceStart, const FVector Normal);


	UFUNCTION(BlueprintImplementableEvent) void EndShoot();
	UFUNCTION(BlueprintImplementableEvent) void EndPressed(const FInputActionValue& Value);
	UFUNCTION(BlueprintImplementableEvent) void Server_ApplyEffectToTarget(FHitResult OutHitResult);
};
