// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_InfoGameState.h"

#include "Actors/A_BasePoint.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Core/WorldGameState.h"
#include "Kismet/GameplayStatics.h"

void UUW_InfoGameState::NativeConstruct()
{
	Super::NativeConstruct();

	if (AWorldGameState* L_AWorldGameState = Cast<AWorldGameState>(GetWorld()->GetGameState()))
	{
		L_AWorldGameState->OnDelegateScoreTeamA.AddUniqueDynamic(this, &UUW_InfoGameState::BindTeamA);
		L_AWorldGameState->OnDelegateScoreTeamB.AddUniqueDynamic(this, &UUW_InfoGameState::BindTeamB);

		ScoreTeamA->SetText(FText::FromString(FString::FromInt(L_AWorldGameState->CurrentScoreTeamA)));
		ScoreTeamB->SetText(FText::FromString(FString::FromInt(L_AWorldGameState->CurrentScoreTeamB)));

	}
}


void UUW_InfoGameState::Create_SmallBasePoint(TSubclassOf<UUW_IconMap> SetWidgetBasePoint)
{
	BasePointInformation->ClearChildren();

	TArray<AActor*>AllBasePoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePoint::StaticClass(), AllBasePoints);
	for (auto& i : AllBasePoints)
	{
		int SelectIndex = -1;
		if (Cast<ABasePoint>(i)->Name == "A") { SelectIndex = 0; }
		else if (Cast<ABasePoint>(i)->Name == "B") { SelectIndex = 1; }
		else if (Cast<ABasePoint>(i)->Name == "C") { SelectIndex = 2; }
		else if (Cast<ABasePoint>(i)->Name == "D") { SelectIndex = 3; }
		else if (Cast<ABasePoint>(i)->Name == "E") { SelectIndex = 4; }
		else if (Cast<ABasePoint>(i)->Name == "F") { SelectIndex = 5; }
		else if (Cast<ABasePoint>(i)->Name == "G") { SelectIndex = 6; }

		UUW_IconMap* L_UUW_IconMap = Cast<UUW_IconMap>(CreateWidget(GetOwningPlayer(), SetWidgetBasePoint));
		L_UUW_IconMap->CreateIconWidget(i);

		BasePointInformation->AddChildToUniformGrid(L_UUW_IconMap, 0, SelectIndex);

	}

}

void UUW_InfoGameState::BindTeamA(int CurrentScoreTeam)
{

	ChangePercent(ProgressBar_TeamA, ScoreTeamA, CurrentScoreTeam);
}

void UUW_InfoGameState::BindTeamB(int CurrentScoreTeam)
{
	ChangePercent(ProgressBar_TeamB, ScoreTeamB, CurrentScoreTeam);
}

void UUW_InfoGameState::ChangePercent(UProgressBar*& SetProgressBar,UTextBlock*& SetTextBlock,int CurrentScore)
{
	SetTextBlock->SetText(FText::FromString(FString::FromInt(CurrentScore)));

	//SetProgressBar->SetPercent(static_cast<float>(CurrentScore) / 
	//	static_cast<float>(Cast<AWorldGameState>(GetWorld()->GetGameState())->StartScore));
}
