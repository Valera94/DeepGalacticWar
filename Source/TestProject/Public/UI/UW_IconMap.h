// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/RepresentativeWidget.h"
#include "UW_IconMap.generated.h"

class UUW_GlobalGameMap;
class AWorldPlayerState;
class AAIController_Base;


UCLASS(Abstract)
class TESTPROJECT_API UUW_IconMap : public UUserWidget, public IRepresentativeWidget
{
	GENERATED_BODY()


public:

	virtual void NativeConstruct() override;

	//0-LayerDeploy,1-LayerPawn,2-LeaderBoard,3-LayerMap
	UFUNCTION(BlueprintImplementableEvent) void Bind_ChangeLayer(const int LayerChange);

	UFUNCTION(BlueprintImplementableEvent) void Bind_GetTeamResult(const int inTeam);

	//0-Neutral,1-Friend,2-Enemy,3-Self
	UFUNCTION(BlueprintImplementableEvent) void ReturnTeamResult(int OutTeamResult);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)void CreateIconWidget(AActor* InAssignedActor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TWeakObjectPtr<AActor>AssignedIconForActor;
	


};
