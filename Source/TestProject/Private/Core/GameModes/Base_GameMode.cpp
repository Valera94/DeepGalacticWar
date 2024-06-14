// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameModes/Base_GameMode.h"

#include "Actors/A_BasePoint.h"
#include "Core/WorldGameState.h"
#include "Core/WorldPlayerState.h"
#include "Kismet/GameplayStatics.h"


AWorld_GameMode::AWorld_GameMode()
{
	bStartPlayersAsSpectators = true;
	MinRespawnDelay = 15;
}

void AWorld_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);


	if (const int32 IndexStart = Options.Find("StartScoreTeamB=", ESearchCase::IgnoreCase, ESearchDir::FromEnd) + FString("StartScoreTeamB=").Len())
	{
		const int32 IndexLast = Options.Find("?", ESearchCase::IgnoreCase, ESearchDir::FromStart, IndexStart);
		StartScoreTeamB = FCString::Atoi(*Options.Mid(IndexStart, IndexLast - IndexStart));
	}

	if (const int32 IndexStart = Options.Find("StartScoreTeamA=", ESearchCase::IgnoreCase, ESearchDir::FromEnd) + FString("StartScoreTeamA=").Len())
	{
		const int32 IndexLast = Options.Find("?", ESearchCase::IgnoreCase, ESearchDir::FromStart, IndexStart);
		StartScoreTeamA = FCString::Atoi(*Options.Mid(IndexStart, IndexLast - IndexStart));
	}

	if (const int32 IndexStart = Options.Find("SecondTimerForGame=", ESearchCase::IgnoreCase, ESearchDir::FromEnd) + FString("SecondTimerForGame=").Len())
	{
		const int32 IndexLast = Options.Find("?", ESearchCase::IgnoreCase, ESearchDir::FromStart, IndexStart);
		SecondTimerForGame = FCString::Atoi(*Options.Mid(IndexStart, IndexLast - IndexStart));
	}

	if (const int32 IndexStart = Options.Find("MinRespawnDelayObject=", ESearchCase::IgnoreCase, ESearchDir::FromEnd) + FString("MinRespawnDelayObject=").Len())
	{
		const int32 IndexLast = Options.Find("?", ESearchCase::IgnoreCase, ESearchDir::FromStart, IndexStart);
		MinRespawnDelayObject = FCString::Atoi(*Options.Mid(IndexStart, IndexLast - IndexStart));
	}

	if (const int32 IndexStart = Options.Find("ScoreKill=", ESearchCase::IgnoreCase, ESearchDir::FromEnd) + FString("ScoreKill=").Len())
	{
		const int32 IndexLast = Options.Find("?", ESearchCase::IgnoreCase, ESearchDir::FromStart, IndexStart);
		ScoreKill = FCString::Atoi(*Options.Mid(IndexStart, IndexLast - IndexStart));
	}
	if (const int32 IndexStart = Options.Find("NumAI=", ESearchCase::IgnoreCase, ESearchDir::FromEnd) + FString("NumAI=").Len())
	{
		const int32 IndexLast = Options.Find("?", ESearchCase::IgnoreCase, ESearchDir::FromStart, IndexStart);
		NumAI = FCString::Atoi(*Options.Mid(IndexStart, IndexLast - IndexStart));
	}

}

void AWorld_GameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*>ArrPawnWithPlayerState;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldPlayerState::StaticClass(), ArrPawnWithPlayerState);

	//Set team for placed AI
	int Select = 2;
	for (auto const& i : ArrPawnWithPlayerState)
	{
		Cast<AWorldPlayerState>(i)->Team = (Select % 2 == 0 ? 1 : 2);
		Select++;
	}


}


void AWorld_GameMode::InitGameState()
{
	Super::InitGameState();

	AWorldGameState* L_CurrentGameState = GetGameState<AWorldGameState>();

	L_CurrentGameState->SecondTimerForGame = SecondTimerForGame;
	L_CurrentGameState->CurrentScoreTeamA = StartScoreTeamA;
	L_CurrentGameState->CurrentScoreTeamB = StartScoreTeamB;

}

void AWorld_GameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	int TeamA = 0, TeamB = 0;
	for (const auto& i : GetGameState<AWorldGameState>()->PlayerArray)
	{
		if (Cast<AWorldPlayerState>(i)->Team == 0) { break; }
		Cast<AWorldPlayerState>(i)->Team == 1 ? TeamA++ : TeamB++;
	}

	NewPlayer->GetPlayerState<AWorldPlayerState>()->Team = TeamB > TeamA ? 1 : 2;
	GetGameState<AWorldGameState>()->NewPlayer(NewPlayer->GetPlayerState<AWorldPlayerState>());

}

void AWorld_GameMode::StartMatch()
{
	Super::StartMatch();

	FTimerHandle L_TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("CreateCharacterAI"));

	GetWorldTimerManager().SetTimer(L_TimerHandle, TimerDelegate, SecondForRespawnChar, false, -1);
}

void AWorld_GameMode::CreateCharacterAI()
{

	if (!StandardAiCharacter) { return; }

	TArray<AActor*> ArrActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePoint::StaticClass(), ArrActors);

	TSet<ABasePoint*> Team1;
	TSet<ABasePoint*> Team2;

	//Check All Base point and try create randomize.
	for (const auto i : ArrActors)
	{
		if (Cast<ABasePoint>(i)->Team == 1)
		{
			Team1.Add(Cast<ABasePoint>(i));
		}
		else if (Cast<ABasePoint>(i)->Team == 2)
		{
			Team2.Add(Cast<ABasePoint>(i));
		}
	}

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.bNoFail = true;
	ActorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::SelectDefaultAtRuntime;

	for (int i = 0; i < NumAI; i++)
	{
		ABasePoint* L_BasePoint =
			(i % 2 == 0 ?
				Team1.Get(FSetElementId::FromInteger(0)) :
				Team2.Get(FSetElementId::FromInteger(0)));

		
		if (AAI_CharBase* L_AAI_CharBase = GetWorld()->SpawnActor<AAI_CharBase>(StandardAiCharacter,
			Cast<ABasePoint>(L_BasePoint)->GetPositionForSpawnCharacter(), ActorSpawnParameters))
		{
			L_AAI_CharBase->SetActorScale3D(FVector::One());
			L_AAI_CharBase->Tags.Add((i % 2 == 0 ? "Team1" : "Team2"));

			if (AWorldPlayerState* L_AWorldPlayerState = Cast<AWorldPlayerState>(L_AAI_CharBase->GetPlayerState()))
			{
				const int L_Team = (i % 2 == 0 ? 1 : 2);
				L_AWorldPlayerState->Team = L_Team;
				L_AWorldPlayerState->OnDelegateTeam.Broadcast(L_AWorldPlayerState->Team);
			}
		}
	};
			   
}
