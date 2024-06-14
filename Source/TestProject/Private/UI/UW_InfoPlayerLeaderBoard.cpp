// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_InfoPlayerLeaderBoard.h"

#include "Core/WorldPlayerState.h"

void UUW_InfoPlayerLeaderBoard::AssignWithPlayerState(APlayerState* WorldPlayerState)
{
	AWorldPlayerState* L_AWorldPlayerState = Cast<AWorldPlayerState>(WorldPlayerState);

	SetKill(L_AWorldPlayerState->Kill);
	SetPoints(L_AWorldPlayerState->Points);
	SetDeath(L_AWorldPlayerState->Death);
	SetAssist(L_AWorldPlayerState->Assist);

	L_AWorldPlayerState->OnDelegateKill.AddUniqueDynamic(this, &UUW_InfoPlayerLeaderBoard::SetKill);
	L_AWorldPlayerState->OnDelegateKill.AddUniqueDynamic(this, &UUW_InfoPlayerLeaderBoard::SetPoints);
	L_AWorldPlayerState->OnDelegateKill.AddUniqueDynamic(this, &UUW_InfoPlayerLeaderBoard::SetDeath);
	L_AWorldPlayerState->OnDelegateKill.AddUniqueDynamic(this, &UUW_InfoPlayerLeaderBoard::SetAssist);

	if(WorldPlayerState==GetOwningPlayerState()){SetColorForText();}
}
