// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_IconMap.h"

#include "Actors/A_BasePoint.h"
#include "Actors/A_TransportBase.h"
#include "Core/PlayerHUD.h"
#include "Core/Characters/Base_Character.h"

void UUW_IconMap::CreateIconWidget_Implementation(AActor* InAssignedActor)
{
	AssignedIconForActor = InAssignedActor;

	//LogicForCreateBasePoint
	if (ABasePoint* L_ABasePoint = Cast<ABasePoint>(AssignedIconForActor))
	{
		if (GetOwningPlayerPawn() == InAssignedActor) { ReturnTeamResult(3); }
		else if (L_ABasePoint->Team == 0) { ReturnTeamResult(0); }
		else if (L_ABasePoint->Team == GetOwningPlayerState<AWorldPlayerState>()->Team) { ReturnTeamResult(1); }
		else { ReturnTeamResult(2); }										 
	}

	//OtherTransport
	if (Cast<A_TransportBase>(AssignedIconForActor))
	{
		ReturnTeamResult(0);
	}

	
}

void UUW_IconMap::NativeConstruct()
{
	Super::NativeConstruct();

	Cast<APlayerHUD>(GetOwningPlayer()->GetHUD())->
		OnDelegateChangeLayer.AddUniqueDynamic(this, &UUW_IconMap::Bind_ChangeLayer);

}