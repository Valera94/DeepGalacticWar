// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_PawnLayer.generated.h"


UCLASS()
class TESTPROJECT_API UUW_PawnLayer : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

};
