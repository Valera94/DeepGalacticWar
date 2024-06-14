// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldPlayerState.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


class UUW_GlobalGameMap;
class ABasePoint;

//0-LayerDeploy,1-LayerPawn,2-LeaderBoard,3-LayerMap
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangeLayer, int, LayerChange); 

UCLASS(Abstract)
class TESTPROJECT_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

	APlayerHUD();
	virtual void BeginPlay() override;

public:

	//0 - WaitDeploy, 1 - PawnView, 2 - TableStatics, 3 - OpenMap, 4 - EndGame
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateChangeLayer OnDelegateChangeLayer;



public:


	UFUNCTION() void BindDelegatePawnIsDie(bool IsDie);

	UFUNCTION(BlueprintCallable) void CreateWidgetAllControlledPawn();
	UFUNCTION() void Bind_Player(AWorldPlayerState* WorldPlayerState);
	UFUNCTION() void Bind_CreateWidgetForPlayer(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);


protected:
	UPROPERTY(BlueprintReadWrite, Category = "MainGameUI|Widgets") UUW_GlobalGameMap* GlobalGameMap;  
	UPROPERTY(BlueprintReadWrite, Category = "MainGameUI|Widgets") UUserWidget* GameStateInfo;		  
	UPROPERTY(BlueprintReadWrite, Category = "MainGameUI|Widgets") UUserWidget* TeamInfoSquad;		  
	


	UPROPERTY(BlueprintReadWrite, Category = "MainGameUI|Layer") UUserWidget* LayerWaitDeploy;	// Activate after die
	UPROPERTY(BlueprintReadWrite, Category = "MainGameUI|Layer") UUserWidget* LayerPawn;		// Activate after possess
	UPROPERTY(BlueprintReadWrite, Category = "MainGameUI|Layer") UUserWidget* LayerLeaderBoard;	// Activate after press "TAB" etc key
	UPROPERTY(BlueprintReadWrite, Category = "MainGameUI|Layer") UUserWidget* LayerMap;			// Activate map
};
