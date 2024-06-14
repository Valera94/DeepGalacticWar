// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_IconOnPawn.h"
#include "Core/WorldPlayerState.h"
#include "Core/Characters/Base_Character.h"
#include "GAS/Attributes/Attribute_Health.h"


bool UUW_IconOnPawn::Initialize()
{

	SetVisibility(ESlateVisibility::Collapsed);

	return Super::Initialize();
}

void UUW_IconOnPawn::AssignToWorldPlayerState(AWorldPlayerState* OtherWorldPlayerState, AWorldPlayerState* OwnerPlayerState)
{
	if (!OtherWorldPlayerState || !OwnerPlayerState) { return; }


	Cast<ABase_Character>(OtherWorldPlayerState->GetPawn())->
	Attribute_Health->OnDelegateDie.AddUniqueDynamic(this, &UUW_IconOnPawn::Bind_Die);

	if(OtherWorldPlayerState->Team==-1)
	{
		Bind_Team(0);
	}
	else if(OtherWorldPlayerState->Team == OwnerPlayerState->Team)
	{
		Cast<ABase_Character>(OtherWorldPlayerState->GetPawn())->
		Attribute_Health->OnDelegateRespawn.AddUniqueDynamic(this, &UUW_IconOnPawn::Bind_Respawn);
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		Bind_Team(1);
	}
	else
	{
		OtherWorldPlayerState->OnDelegateIsDetected.AddUniqueDynamic(this, &UUW_IconOnPawn::Bind_Detected);
		SetVisibility(ESlateVisibility::Collapsed);
		Bind_Team(2);
	}

}

void UUW_IconOnPawn::Bind_Team_Implementation(int CurrentTeam)
{
	SetVisibility(Cast<AWorldPlayerState>(GetOwningPlayerState())->Team == CurrentTeam? 
								ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
}

void UUW_IconOnPawn::Bind_Detected_Implementation(const bool IsDetected)
{
	SetVisibility(IsDetected == true ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}

void UUW_IconOnPawn::Bind_Die_Implementation()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UUW_IconOnPawn::Bind_Respawn_Implementation()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}
