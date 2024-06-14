// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_BasePoint_IconMap.h"

#include "Actors/A_BasePoint.h"
#include "Components/Button.h"

void UUW_BasePoint_IconMap::NativeConstruct()
{
	Super::NativeConstruct();

}

void UUW_BasePoint_IconMap::CreateIconWidget_Implementation(AActor* InAssignedActor)
{
	Super::CreateIconWidget_Implementation(InAssignedActor);

	if (ABasePoint* L_ABasePoint = Cast<ABasePoint>(InAssignedActor))
	{
		L_ABasePoint->OnDelegateChangeTeam.AddUniqueDynamic(this, &UUW_BasePoint_IconMap::Bind_GetTeamResult);
		Bind_GetTeamResult(L_ABasePoint->Team);
		NameBasePoint->SetText(FText::FromName(L_ABasePoint->Name));

		Cast<ABasePoint>(AssignedIconForActor)->OnDelegateChangeTeam.AddUniqueDynamic(this, &UUW_BasePoint_IconMap::Bind_GetTeamResult);
	}

}