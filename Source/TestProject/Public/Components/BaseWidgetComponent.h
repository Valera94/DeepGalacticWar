// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BaseWidgetComponent.generated.h"

class AWorldPlayerState;
class UUW_IconOnPawn;

UCLASS()
class TESTPROJECT_API UBaseWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

	UBaseWidgetComponent();
	virtual void InitWidget() override;

public:
	UFUNCTION() void AssignWidgetToNeedCLass(AWorldPlayerState* OtherWorldPlayerState, AWorldPlayerState* OwnerPlayerState);
	UFUNCTION() void Bind_Pawn(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);
	UFUNCTION() void Bind_Team(const int Team);

	virtual void OnAttachmentChanged() override;

	UPROPERTY()	AWorldPlayerState* AssignedWorldPlayerStateAttached;
	UPROPERTY()	AWorldPlayerState* OwnerWorldPlayerState;
};
