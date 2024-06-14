// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RulesForSpawn.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URulesForSpawn : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TESTPROJECT_API IRulesForSpawn
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//1-Game 2-WaitRestart 3-Dead 4-EndGame
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ChangeScenario(int SelectScenario);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void PressedPlaceActorForSpawn(AActor* ActorWhenSpawn);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DisableSelectedIconPlaceSpawn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReadyDeploy();
};
