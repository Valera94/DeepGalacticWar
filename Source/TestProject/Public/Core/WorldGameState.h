// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Characters/AI_CharBase.h"
#include "GameFramework/GameState.h"		 
#include "WorldGameState.generated.h"

class AAI_CharBase;
class AWorldPlayerState;
class ABasePoint;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateNewPlayer, AWorldPlayerState*, WorldPlayerState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateScoreTeamA, int, ScoreTeam);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateScoreTeamB, int, ScoreTeam);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTimer, int, ScoreTeam);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegateEndMatch);


UCLASS(Abstract)
class TESTPROJECT_API AWorldGameState : public AGameState
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	/*-----Timer----*/
	FTimerHandle TimerCalculateScoreTeamUseBasePoint;
	/*-------------*/

#pragma region |* Score *|

	/*-- Delegate --*/
	UFUNCTION() void CalculateScoreUseBasePoint();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateScoreTeamA OnDelegateScoreTeamA;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateScoreTeamB OnDelegateScoreTeamB;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateNewPlayer OnDelegateNewPlayer;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateEndMatch OnDelegateEndMatch;


	UFUNCTION() void OnRep_CurrentScoreTeamA(int SetCurrentScoreTeamA);
	UPROPERTY(ReplicatedUsing=OnRep_CurrentScoreTeamA, BlueprintReadOnly, Transient, Category = "InfoGame|Score")
	int CurrentScoreTeamA;

	UFUNCTION() void OnRep_CurrentScoreTeamB(int SetCurrentScoreTeamB);
	UPROPERTY(ReplicatedUsing = OnRep_CurrentScoreTeamB, BlueprintReadOnly, Transient, Category = "InfoGame|Score")
	int CurrentScoreTeamB;


	UPROPERTY(Replicated,BlueprintReadOnly, Transient, Category = "StartInfoGame")
	int SecondTimerForGame;

	UFUNCTION()void NewPlayer(AWorldPlayerState* SetWorldPlayerState);

	UFUNCTION(NetMulticast,Reliable)void NetMulticast_EndMatch();

#pragma endregion

private:





};
