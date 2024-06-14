// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"					   
#include "Components/AC_Weapon.h"
#include "GAS/AC_AbilitySystem.h"
#include "Base_Character.generated.h"

class AWorldPlayerState;
class UAIPerceptionStimuliSourceComponent;
class UAttribute_Weapon;
class UCameraComponent;
class USpringArmComponent;
class UWidgetBlueprint;
class UAttribute_Health;
class UAC_AbilitySystem;

DECLARE_LOG_CATEGORY_EXTERN(LOG_BaseCharacter, All, All);

UCLASS(BlueprintType, Blueprintable)
class TESTPROJECT_API ABase_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:


	ABase_Character(const FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent()const override { return Cast<UAbilitySystemComponent>(AbilitySystemComponent); }


#pragma region |* StartComponent *|
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere) TObjectPtr<UAIPerceptionStimuliSourceComponent> AIPerceptionStimuliSourceComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) float DefaultHealth = 100.f;

	/* Default property */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess)) TObjectPtr<UAC_AbilitySystem> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess)) TObjectPtr<UAttribute_Health> Attribute_Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess)) TObjectPtr<UAC_Weapon> AC_Weapon;

	/* Die */
	//UFUNCTION(BlueprintCallable)		void  DieCharacter();
	UFUNCTION(BlueprintCallable, Server, Reliable)	void  Server_DieCharacter_Reliable();
	UFUNCTION(NetMulticast, Reliable)				void  NetMulticast_DieCharacter_Reliable();

	/* Respawn */
	//UFUNCTION(BlueprintCallable)		void  Respawn(FVector LocationForRespawn);
	UFUNCTION(BlueprintCallable,Server, Reliable)	void  Server_Respawn_Reliable(FVector LocationForRespawn);
	UFUNCTION(NetMulticast, Reliable)				void  NetMulticast_Respawn_Reliable(FVector LocationForRespawn);


	UFUNCTION()void Bind_ChangeHealth(float CurrentHealthFromAttribute);
	UFUNCTION()void Bind_EndGame();

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere) bool IsDie = false;


	UFUNCTION(BlueprintCallable, BlueprintPure) int GetTeamCharacter();
};