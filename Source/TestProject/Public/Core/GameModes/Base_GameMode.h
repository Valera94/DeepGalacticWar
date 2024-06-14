// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Base_GameMode.generated.h"

class AAI_CharBase;


UCLASS(Abstract)
class TESTPROJECT_API AWorld_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AWorld_GameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void InitGameState() override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual void StartMatch() override;

	UFUNCTION() void CreateCharacterAI();

	//Default AI Pawn with brain
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)TSubclassOf<AAI_CharBase> StandardAiCharacter;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int StartScoreTeamB = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int StartScoreTeamA = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int SecondTimerForGame = 350;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int MinRespawnDelayObject = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int ScoreKill = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int NumAI = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int SecondForRespawnChar = 8;

};


