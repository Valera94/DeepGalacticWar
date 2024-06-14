// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UW_InfoPlayerLeaderBoard.generated.h"

class AWorldPlayerState;
class UTextBlock;

UCLASS(Abstract)
class TESTPROJECT_API UUW_InfoPlayerLeaderBoard : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget)) UTextBlock* Points;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget)) UTextBlock* Death;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget)) UTextBlock* Kill;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget)) UTextBlock* Assist;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget)) UTextBlock* Ping;

	UFUNCTION(BlueprintImplementableEvent)void SetColorForText();

	UFUNCTION(BlueprintCallable)void SetKill(int SetKill) { Kill->SetText(FText::FromString(FString::FromInt(SetKill))); }
	UFUNCTION(BlueprintCallable)void SetPoints(int SetPoints) { Points->SetText(FText::FromString(FString::FromInt(SetPoints)));}
	UFUNCTION(BlueprintCallable)void SetDeath(int SetDeath) { Death->SetText(FText::FromString(FString::FromInt(SetDeath))); }
	UFUNCTION(BlueprintCallable)void SetAssist(int SetAssist) { Assist->SetText(FText::FromString(FString::FromInt(SetAssist))); }

	void AssignWithPlayerState(APlayerState* WorldPlayerState);

};
