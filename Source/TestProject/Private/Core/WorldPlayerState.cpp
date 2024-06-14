// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WorldPlayerState.h"

#include "Core/WorldGameState.h"
#include "Core/Characters/PlayerCharacter.h"
#include "Net/UnrealNetwork.h"

void AWorldPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Death)				;
		DOREPLIFETIME(ThisClass, Kill)			;
		DOREPLIFETIME(ThisClass, Assist)		;
		DOREPLIFETIME(ThisClass, Points)		;
		DOREPLIFETIME(ThisClass, Team)			;
		DOREPLIFETIME(ThisClass, bIsDetected)	;
}

AWorldPlayerState::AWorldPlayerState()
{
}

void AWorldPlayerState::OnRep_Owner()
{
	Super::OnRep_Owner();
}

void AWorldPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(Cast<APlayerCharacter>(GetPawn()))
	{
		SetIsABot(false);
	}
	else
	{
		SetIsABot(true);
	}

}

void AWorldPlayerState::Activate_IsDetected(bool IsDetected)
{

	bIsDetected = IsDetected;
	OnRepIsDetected();
	OnDelegateIsDetected.Broadcast(IsDetected);
}

int AWorldPlayerState::GetTeamResult(const int OtherTeam) const
{
	if (!OtherTeam || Team == -1) { return -1; }
	if (OtherTeam == 0 || Team == 0) { return 0; }
	else if (Team == OtherTeam) { return 1; }
	return 2;
}
