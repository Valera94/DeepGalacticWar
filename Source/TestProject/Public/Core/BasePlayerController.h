// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UPoolWidgetComponents;
class UPDA_DataAssetObjectsGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegatePawnIsDie, bool, IsDie);


UCLASS(Abstract)
class TESTPROJECT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegatePawnIsDie	OnDelegatePawnIsDie;


protected:

	ABasePlayerController(const FObjectInitializer& ObjectInitializer);
	virtual void AcknowledgePossession(APawn* P) override;
	virtual void ServerAcknowledgePossession_Implementation(APawn* P) override;

};
