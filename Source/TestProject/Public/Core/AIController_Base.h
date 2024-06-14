// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegateShoot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnCanFight);
//If we cover into smoke we can hidden from other widgets, and etc. Can be global error map etc. 

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangeStatus,FString, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegateAIDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegateAIRespawn);



UCLASS()
class TESTPROJECT_API AAIController_Base : public AAIController
{
	GENERATED_BODY()

public:

	AAIController_Base();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
																 
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FDelegateShoot OnDelegateShoot;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FDelegateChangeStatus OnDelegateChangeStatus;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FDelegateAIDie OnDelegateAIDie;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FDelegateAIRespawn OnDelegateAIRespawn;

	UPROPERTY(BlueprintReadWrite,EditAnywhere) bool AIIsDie = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere) bool AICanFight = true;


	UFUNCTION()void Bind_DetectedPawnThisAIController(bool IsDetected);
	FTimerHandle TimerDetectedPawn;

	UFUNCTION()void Bind_DiePawnController();
	UFUNCTION()void EndGame();
};
