// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GA_Shoot.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Core/Characters/Base_Character.h"
#include "Actors/A_Weapon.h"
#include "Core/Characters/PlayerCharacter.h"

UGA_Shoot::UGA_Shoot()
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Shoot::Shoot()
{
	//if (!IsLocallyControlled()) { return; }

	if (const APlayerCharacter* L_BaseCharacter = Cast<APlayerCharacter>(GetAbilitySystemComponentFromActorInfo()->GetAvatarActor()))
	{

		if (UEnhancedInputComponent* L_UEnhancedInputComponent = Cast<UEnhancedInputComponent>(L_BaseCharacter->InputComponent))
		{
			//BindLeftClick
			if (L_BaseCharacter->AC_Weapon->CurrentWeapon->GetTypeShot() == ETypeShot::MultiplyShot)
			{
				L_UEnhancedInputComponent->BindAction(L_BaseCharacter->AllStructInput.StructInput_LeftClick.InputAction, ETriggerEvent::Completed, this, &UGA_Shoot::EndPressed);
			}
			else
			{
				L_UEnhancedInputComponent->ClearBindingsForObject(this);
			}
		}
		//L_BaseCharacter->OnDelegateLeftClick.RemoveDynamic(this, &UGA_Shoot::EndPressed);

		ETypeShot L_ETypeShot = L_BaseCharacter->AC_Weapon->CurrentWeapon->GetTypeShot();

		switch (L_ETypeShot)
		{
		case ETypeShot::SingleShot:

			StartRangedWeaponTargeting();
			EndShoot();

			break;

		case ETypeShot::SequenceShot:

			for (int i = 0; i < L_BaseCharacter->AC_Weapon->CurrentWeapon->GetNumSequenceShot(); ++i)
			{
				StartRangedWeaponTargeting();
			}
			EndShoot();

			break;

		case ETypeShot::MultiplyShot:

			StartRangedWeaponTargeting();

			break;
		}
	}
	else
	{
		StartRangedWeaponTargeting();
	}
}

void UGA_Shoot::StartRangedWeaponTargeting()
{
	UAC_Weapon* L_UAC_Weapon = GetAvatarActorFromActorInfo()->GetComponentByClass<UAC_Weapon>();
	if (L_UAC_Weapon)
	{
		if (!L_UAC_Weapon->CurrentWeapon && L_UAC_Weapon->CurrentWeapon->IsEmptyAmmoInClip()) { return; } // if no amm we no shoot
	}

	FHitResult L_HitResult;
	if (Cast<APlayerCharacter>(GetAvatarActorFromActorInfo()))
	{
		L_HitResult = L_UAC_Weapon->CurrentWeapon->GetHitResultWeapon();
	}
	else
	{
		L_HitResult = L_UAC_Weapon->CurrentWeapon->GetHitResultWeapon_AI();
	}



	FGameplayAbilityTargetData_SingleTargetHit* GameplayAbilityTargetData = new FGameplayAbilityTargetData_SingleTargetHit();

	GameplayAbilityTargetData->HitResult = L_HitResult;
	bool Result = false;

	if (L_HitResult.GetActor() != nullptr && L_HitResult.GetActor()->GetComponentByClass<UAbilitySystemComponent>() != nullptr)
	{
		Result = true;
	}

	const FVector End = L_HitResult.IsValidBlockingHit() ? L_HitResult.Location : L_HitResult.TraceEnd;
	Server_OnRangedWeaponTargetDataReady(Result, End, L_HitResult.TraceStart, L_HitResult.Normal);
}

void UGA_Shoot::Server_OnRangedWeaponTargetDataReady_Implementation(const bool ActivateTraceFromServer,
	const FVector TraceEnd, const FVector TraceStart, const FVector Normal)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString("ReadyWeaponTargetData"));
	if (UAC_Weapon* L_UAC_Weapon = GetAvatarActorFromActorInfo()->GetComponentByClass<UAC_Weapon>())
	{
		if (L_UAC_Weapon->CurrentWeapon && !L_UAC_Weapon->CurrentWeapon->IsEmptyAmmoInClip())
		{

			if (ActivateTraceFromServer)
			{
				FHitResult HitResult;
				FTraceDelegate TraceDelegate;
				TraceDelegate.BindLambda([this](const FTraceHandle& handle, FTraceDatum& data)
					{
						if (data.OutHits.IsValidIndex(0))
						{
							if (FHitResult* HitResultTemp = &data.OutHits[0])
							{
								Server_ApplyEffectToTarget(*HitResultTemp);
							}
						}
					});

				FTraceHandle TraceHandle = GetWorld()->AsyncLineTraceByChannel(EAsyncTraceType::Single, TraceStart, TraceEnd, ECC_Pawn,
					FCollisionQueryParams::DefaultQueryParam, FCollisionResponseParams::DefaultResponseParam, &TraceDelegate);
			}
			L_UAC_Weapon->CurrentWeapon->Server_Shoot();

			FGameplayCueParameters GameplayCueParameters;
			GameplayCueParameters.Location = TraceEnd;
			GameplayCueParameters.Normal = Normal;
			K2_ExecuteGameplayCueWithParams(ActivateGameplayCueTag, GameplayCueParameters);

			if (!Cast<APlayerCharacter>(GetActorInfo().AvatarActor))
			{
				EndShoot();
				//bool HasAuthority(const FGameplayAbilityActivationInfo * ActivationInfo) const;
			}
		}
	}


}
