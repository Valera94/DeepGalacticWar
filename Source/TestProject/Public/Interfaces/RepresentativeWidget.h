// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RepresentativeWidget.generated.h"

class UUW_IconMap;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URepresentativeWidget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TESTPROJECT_API IRepresentativeWidget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void SelectedWidgetPlaceForDeploy(UUW_IconMap* SelectedIconMap);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void GetActorSelectedWidgetPlaceForDeploy(AActor* SelectedActor);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void RealizationDeploy(FVector LocationDeploy);
	//0-WaitDeployed, 1-Game
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void ChangeStatusPlayerUI(int StatusUIPlayer);

};
