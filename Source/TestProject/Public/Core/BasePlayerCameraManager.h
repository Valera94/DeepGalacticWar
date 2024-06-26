// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "BasePlayerCameraManager.generated.h"

UCLASS()
class TESTPROJECT_API ABasePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UFUNCTION() void ToggleActivateFadeWhenDiePawn(bool PawnIsDie);

};
