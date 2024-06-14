// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BasePlayerCameraManager.h"

#include "Core/BasePlayerController.h"

class ABasePlayerController;

void ABasePlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
	ToggleActivateFadeWhenDiePawn(true);

	Cast<ABasePlayerController>(GetOwner())->OnDelegatePawnIsDie.AddUniqueDynamic(this, &ABasePlayerCameraManager::ToggleActivateFadeWhenDiePawn);

}

void ABasePlayerCameraManager::ToggleActivateFadeWhenDiePawn(bool PawnIsDie)
{
	if (PawnIsDie)
	{
		StartCameraFade(0.9, 1, 0, FLinearColor::Black,false,true);
	}
	else
	{
		StartCameraFade(1, 0, 0, FLinearColor::Black, false, true);
	}

}
