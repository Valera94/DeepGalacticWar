// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "ConsoleCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UConsoleCheatManager : public UCheatManager
{
	GENERATED_BODY()

protected:
	virtual void InitCheatManager() override;




};
