// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/A_Weapon.h"
#include "AC_Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangeWeapon, AA_Weapon*, CurrentWeapon);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTPROJECT_API UAC_Weapon : public UActorComponent
{
	GENERATED_BODY()

public:

	UAC_Weapon();
	virtual void InitializeComponent() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateChangeWeapon OnDelegateChangeWeapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)TSubclassOf<AA_Weapon>Weapon;
	UPROPERTY(Replicated, BlueprintReadOnly)AA_Weapon* CurrentWeapon;
	UFUNCTION(Server, Reliable)void Server_CreateWeapon();

};
