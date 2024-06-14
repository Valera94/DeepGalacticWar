// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WorldGameState.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "Actors/A_BasePoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/Characters/AI_CharBase.h"
#include "Core/GameModes/Base_GameMode.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void AWorldGameState::BeginPlay()
{
	Super::BeginPlay();


	// =========================== Add Player Char To Arr ============================================

	if (HasAuthority())
	{
		FTimerDynamicDelegate TimerDynamicDelegate;
		TimerDynamicDelegate.BindDynamic(this, &AWorldGameState::CalculateScoreUseBasePoint);
		GetWorldTimerManager().SetTimer(TimerCalculateScoreTeamUseBasePoint, TimerDynamicDelegate, 1, true);


		OnRep_CurrentScoreTeamB(CurrentScoreTeamB);
		OnRep_CurrentScoreTeamA(CurrentScoreTeamA);
	}
}

void AWorldGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentScoreTeamA);
	DOREPLIFETIME(ThisClass, CurrentScoreTeamB);
	DOREPLIFETIME(ThisClass, SecondTimerForGame);
}

void AWorldGameState::CalculateScoreUseBasePoint()
{
	if (HasAuthority()) {

		TArray<AActor*>AllBasePointGame;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePoint::StaticClass(), AllBasePointGame);

		int L_TeamA = 0, L_TeamB = 0;
		for (const auto i : AllBasePointGame)
		{
			if (ABasePoint* L_ABasePoint = Cast<ABasePoint>(i))
			{
				if (L_ABasePoint->Team != 0)
				{
					L_ABasePoint->Team == 1 ? L_TeamA++ : L_TeamB++;
				}
			}
		}
		if (L_TeamA != L_TeamB)
		{
			const int L_SubScore = FMath::Abs(L_TeamA - L_TeamB);

			L_TeamA > L_TeamB ?	//To Server
				OnDelegateScoreTeamB.Broadcast(CurrentScoreTeamB = CurrentScoreTeamB - L_SubScore) :
				OnDelegateScoreTeamA.Broadcast(CurrentScoreTeamA = CurrentScoreTeamA - L_SubScore);

			L_TeamA > L_TeamB ?	//To Client
				OnRep_CurrentScoreTeamB(CurrentScoreTeamB) :
				OnRep_CurrentScoreTeamA(CurrentScoreTeamA);


		}

		if (CurrentScoreTeamB <= 0 || CurrentScoreTeamA <= 0 || SecondTimerForGame - GetServerWorldTimeSeconds() <= 0)
		{
			GetWorldTimerManager().ClearTimer(TimerCalculateScoreTeamUseBasePoint);
			NetMulticast_EndMatch();
			SetMatchState(MatchState::WaitingPostMatch);
			SetMatchState(MatchState::LeavingMap);  
		}
	}
}

void AWorldGameState::OnRep_CurrentScoreTeamA(int SetCurrentScoreTeamA)
{
	OnDelegateScoreTeamA.Broadcast(SetCurrentScoreTeamA);
}

void AWorldGameState::OnRep_CurrentScoreTeamB(int SetCurrentScoreTeamB)
{
	OnDelegateScoreTeamB.Broadcast(SetCurrentScoreTeamB);
}

void AWorldGameState::NewPlayer(AWorldPlayerState* SetWorldPlayerState)
{
	OnDelegateNewPlayer.Broadcast(SetWorldPlayerState);
}

void AWorldGameState::NetMulticast_EndMatch_Implementation()
{
	OnDelegateEndMatch.Broadcast();

}


