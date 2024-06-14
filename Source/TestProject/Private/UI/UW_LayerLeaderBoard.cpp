// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_LayerLeaderBoard.h"

#include "Components/VerticalBox.h"
#include "Core/WorldPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "UI/UW_InfoPlayerLeaderBoard.h"


void UUW_LayerLeaderBoard::NativeConstruct()
{
	Super::NativeConstruct();

	Create_InfoPlayerLeaderBoard();
}

void UUW_LayerLeaderBoard::Create_InfoPlayerLeaderBoard()
{
	if (!TypeWidget_InfoPlayerLeaderBoard) { check(TypeWidget_InfoPlayerLeaderBoard); return; }

	for (auto& i : GetWorld()->GetGameState()->PlayerArray)
	{
		const int L_Team = Cast<AWorldPlayerState>(i)->Team;
		if (L_Team == 0) { return; }

		UUW_InfoPlayerLeaderBoard* L_UW_InfoPlayerLeaderBoard =
			Cast<UUW_InfoPlayerLeaderBoard>(CreateWidget(GetOwningPlayer(), TypeWidget_InfoPlayerLeaderBoard));

		L_UW_InfoPlayerLeaderBoard->AssignWithPlayerState(i);


		L_Team == 1 ?
			VerticalBox_TeamA->AddChildToVerticalBox(L_UW_InfoPlayerLeaderBoard) :
			VerticalBox_TeamB->AddChildToVerticalBox(L_UW_InfoPlayerLeaderBoard);


	}
}
