// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "InputActionValue.h"
#include "GAS/AC_AbilitySystem.h"
#include "GameFramework/Actor.h"
#include "A_Weapon.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ABaseCharacter;
class UAttribute_Weapon;


UENUM(BlueprintType, Blueprintable)
enum class ETypeShot : uint8
{
	SingleShot,
	SequenceShot,
	MultiplyShot
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangedTypeShot, ETypeShot, NewTypeShot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateCurrentAmmoInClip, int, CurrentAmmoInClip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateCurrentTotalAmmo, int, CurrentTotalAmmo);


UCLASS()
class TESTPROJECT_API AA_Weapon : public AActor
{
	GENERATED_BODY()

public:

	AA_Weapon();
	virtual void BeginPlay() override;
public:

	/* WorldPresentation */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;


	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateChangedTypeShot OnDelegateChangedTypeShot;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateCurrentTotalAmmo OnDelegateCurrentTotalAmmo;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateCurrentAmmoInClip OnDelegateCurrentAmmoInClip;


public:
	UFUNCTION(BlueprintCallable)void SetAim(bool IsAim);

	UFUNCTION(Server, Reliable, BlueprintCallable)void Server_Reload();
	UFUNCTION(Server, Reliable)void Server_Shoot();
	UFUNCTION(Client, Reliable)void SendMessage(int SetCurrent_AmmoInClip, int SetCurrent_TotalAmmo);

	UFUNCTION()void IsDieAttachParent(bool IsDie);

	UFUNCTION(BlueprintCallable) void ChangeTypeShot(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)void Fire(const TArray<FVector>& ImpactPositions, const TArray<FVector>& ImpactNormal);

	UFUNCTION(BlueprintCallable, BlueprintPure) bool IsEmptyAmmoInClip();

	UFUNCTION(BlueprintCallable, BlueprintPure) USkeletalMesh* GetMeshWeapon() { return SkeletalMeshComponent.Get()->GetSkeletalMeshAsset(); }
	UFUNCTION(BlueprintCallable, BlueprintPure) ETypeShot GetTypeShot() { return CurrentTypeShot; }
	UFUNCTION(BlueprintCallable, BlueprintPure) FHitResult GetHitResultWeapon();
	UFUNCTION(BlueprintCallable, BlueprintPure) FHitResult GetHitResultWeapon_AI();
	UFUNCTION(BlueprintCallable, BlueprintPure) int GetNumSequenceShot() { return NumSequenceShot; };
	UFUNCTION(BlueprintCallable, BlueprintPure) int GetCurrentAmmoInClip() { return Current_AmmoInClip; };
	UFUNCTION(BlueprintCallable, BlueprintPure) int GetCurrentTotalAmmo() { return Current_TotalAmmo; };

private:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ConstructInfo|TypeShot", meta = (AllowPrivateAccess))	ETypeShot CurrentTypeShot = ETypeShot::SingleShot;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ConstructInfo|TypeShot", meta = (AllowPrivateAccess)) bool SingleShot = true;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ConstructInfo|TypeShot", meta = (AllowPrivateAccess)) bool SequenceShot = true;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ConstructInfo|TypeShot", meta = (AllowPrivateAccess)) int NumSequenceShot = 3;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ConstructInfo|TypeShot", meta = (AllowPrivateAccess)) bool MultiplyShot = true;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ConstructInfo|Ammo|Standart", meta = (AllowPrivateAccess)) int Max_AmmoInClip = 30;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ConstructInfo|Ammo|Standart", meta = (AllowPrivateAccess)) int Max_TotalAmmo = 60;

	UPROPERTY(BlueprintReadWrite, BlueprintGetter = GetCurrentAmmoInClip, EditDefaultsOnly, Category = "ConstructInfo|Ammo", meta = (AllowPrivateAccess))
	int Current_AmmoInClip = Max_AmmoInClip; //etc CurrentWeaponInClip
	UPROPERTY(BlueprintReadWrite, BlueprintGetter = GetCurrentTotalAmmo, EditDefaultsOnly, Category = "ConstructInfo|Ammo", meta = (AllowPrivateAccess))
	int Current_TotalAmmo = Max_TotalAmmo;  //all current weapons

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ConstructInfo|Ammo", meta = (AllowPrivateAccess)) int CostOfOneShot = 1;	//price 1 shot
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ConstructInfo|Ammo", meta = (AllowPrivateAccess)) float DelayBetweenShot = 1.f;




};
