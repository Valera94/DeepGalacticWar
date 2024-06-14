// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_Pawn_IconMap.h"

#include "Core//AIController_Base.h"
#include "Core/WorldPlayerState.h"
#include "Core/Characters/Base_Character.h"
#include "GAS/Attributes/Attribute_Health.h"
#include "UI/UW_BasePoint_IconMap.h"
#include "UI/UW_GlobalGameMap.h"


bool UUW_Pawn_IconMap::Initialize()
{
	SetVisibility(ESlateVisibility::Collapsed);
	return Super::Initialize();
}

void UUW_Pawn_IconMap::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	AssignedGlobalGameMap->UpdateLocationOnTheMap(AssignedIconForActor.Get(), this);
	AssignedGlobalGameMap->UpdateRotationOnTheMap(AssignedIconForActor.Get(), this);
}

void UUW_Pawn_IconMap::CalculateTeamResultPawn(const int Team)
{

	if (Team == -1) { return; }

	if (Team == 0) { ReturnTeamResult(0); }
	else if (Team == GetOwningPlayerState<AWorldPlayerState>()->Team)
	{
		ReturnTeamResult(1);

		Cast<ABase_Character>(AssignedIconForActor)->Attribute_Health->OnDelegateRespawn.AddUniqueDynamic(this, &UUW_Pawn_IconMap::Bind_Respawn);

	}
	else { ReturnTeamResult(2); }

}
				 PRAGMA_DISABLE_OPTIMIZATION
void UUW_Pawn_IconMap::Bind_OnPawnSet(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	if (!GetOwningPlayerState()) { return; }
	if (OldPawn)
	{
		if (ABase_Character* L_ABase_Character = Cast<ABase_Character>(OldPawn))
		{
			if (Cast<AWorldPlayerState>(Player)->Team == Cast<AWorldPlayerState>(GetOwningPlayerState())->Team)
			{
				L_ABase_Character->Attribute_Health->OnDelegateRespawn.RemoveDynamic(this, &UUW_Pawn_IconMap::Bind_Respawn);
			}

			L_ABase_Character->Attribute_Health->OnDelegateDie.RemoveDynamic(this, &UUW_Pawn_IconMap::Bind_Die);
			Bind_Die();
		}
	}

	if (NewPawn)
	{
		if (ABase_Character* L_ABase_Character = Cast<ABase_Character>(NewPawn))
		{
			if (Cast<AWorldPlayerState>(Player)->Team == Cast<AWorldPlayerState>(GetOwningPlayerState())->Team)
			{
				L_ABase_Character->Attribute_Health->OnDelegateRespawn.AddUniqueDynamic(this, &UUW_Pawn_IconMap::Bind_Respawn);
				Bind_Respawn();
			}
			L_ABase_Character->Attribute_Health->OnDelegateDie.AddUniqueDynamic(this, &UUW_Pawn_IconMap::Bind_Die);
		}
	}
}

void UUW_Pawn_IconMap::Bind_DetectedController_Implementation(const bool IsDetected)
{
	SetVisibility(IsDetected == true ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}

void UUW_Pawn_IconMap::Bind_Die_Implementation()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UUW_Pawn_IconMap::Bind_Respawn_Implementation()
{
	SetVisibility(ESlateVisibility::Visible);
	CreateIconWidget(AssignedPlayerState->GetPawn());
}

void UUW_Pawn_IconMap::AssignToOtherPlayerState_Implementation(AWorldPlayerState* State, UUW_GlobalGameMap* GlobalGameMap)
{

	AssignedGlobalGameMap = GlobalGameMap;
	AssignedPlayerState = State;

	AssignedPlayerState->OnPawnSet.AddUniqueDynamic(this, &ThisClass::Bind_OnPawnSet);
	AssignedPlayerState->OnDelegateTeam.AddUniqueDynamic(this, &UUW_Pawn_IconMap::Bind_GetTeamResult);
	AssignedPlayerState->OnDelegateIsDetected.AddUniqueDynamic(this, &UUW_Pawn_IconMap::Bind_DetectedController);

	if (AssignedPlayerState == GetOwningPlayerState()){ReturnTeamResult(3);}//If this is mine pawn
	else if (AssignedPlayerState->GetPawn())
	{
		Bind_OnPawnSet(State,State->GetPawn(),nullptr);
		CreateIconWidget(AssignedPlayerState->GetPawn());
	}


}
