// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_LayerLeaderBoard.generated.h"

class UUW_InfoPlayerLeaderBoard;
class UVerticalBox;

UCLASS(Abstract)
class TESTPROJECT_API UUW_LayerLeaderBoard : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UUW_InfoPlayerLeaderBoard> TypeWidget_InfoPlayerLeaderBoard;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))UVerticalBox* VerticalBox_TeamA;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))UVerticalBox* VerticalBox_TeamB;

	void Create_InfoPlayerLeaderBoard();
};
