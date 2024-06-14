// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_IconMap.h"
#include "Blueprint/UserWidget.h"
#include "UW_InfoGameState.generated.h"

class UProgressBar;
class UTextBlock;
class UUniformGridPanel;

UCLASS()
class TESTPROJECT_API UUW_InfoGameState : public UUserWidget
{
	GENERATED_BODY()


	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))UTextBlock* ScoreTeamA;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))UTextBlock* ScoreTeamB;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))UTextBlock* RemainingTime;

	UPROPERTY(meta = (BindWidget))UUniformGridPanel* BasePointInformation;

	UPROPERTY(meta = (BindWidget))UProgressBar* ProgressBar_TeamA;
	UPROPERTY(meta = (BindWidget))UProgressBar* ProgressBar_TeamB;


	UFUNCTION(BlueprintCallable)void Create_SmallBasePoint(TSubclassOf<UUW_IconMap> SetWidgetBasePoint);

	UFUNCTION()void BindTeamA(int CurrentScoreTeam);
	UFUNCTION()void BindTeamB(int CurrentScoreTeam);

	void ChangePercent(UProgressBar*& SetProgressBar, UTextBlock*& SetTextBlock, int CurrentScore);
};
