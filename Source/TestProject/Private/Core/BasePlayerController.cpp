// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BasePlayerController.h"

#include "Core/ConsoleCheatManager.h"
#include "Core/Characters/Base_Character.h"
#include "Kismet/GameplayStatics.h"


ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CheatClass = UConsoleCheatManager::StaticClass();

}

void ABasePlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (ABase_Character* CharacterBase = Cast<ABase_Character>(P))
	{
		CharacterBase->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterBase, CharacterBase);
	}

	OnDelegatePawnIsDie.Broadcast(false);
}

void ABasePlayerController::ServerAcknowledgePossession_Implementation(APawn* P)
{
	Super::ServerAcknowledgePossession_Implementation(P);

	OnDelegatePawnIsDie.Broadcast(false);
}

