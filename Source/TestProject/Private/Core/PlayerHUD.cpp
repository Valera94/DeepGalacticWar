// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerHUD.h"
#include "Core/BasePlayerController.h"
#include "Core/WorldGameState.h"
#include "Core/WorldPlayerState.h"


APlayerHUD::APlayerHUD()
{
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if(Cast<ABasePlayerController>(GetOwningPlayerController()))
	{
		Cast<ABasePlayerController>(GetOwningPlayerController())->OnDelegatePawnIsDie.AddUniqueDynamic(this, &APlayerHUD::BindDelegatePawnIsDie);
	}
}

void APlayerHUD::BindDelegatePawnIsDie(bool IsDie)
{
	if (IsDie)
	{
		OnDelegateChangeLayer.Broadcast(0);
	}
}

void APlayerHUD::CreateWidgetAllControlledPawn()
{
	if (GetOwningPlayerController()->GetPlayerState < AWorldPlayerState>())
	{
		for (const auto& i : GetWorld()->GetGameState<AWorldGameState>()->PlayerArray)
		{
			if (Cast<AWorldPlayerState>(i) && GetOwningPlayerController()->GetPlayerState<AWorldPlayerState>() != i)
			{
				Bind_Player(Cast<AWorldPlayerState>(i));
			}
		}
	}
}

void APlayerHUD::Bind_Player(AWorldPlayerState* InWorldPlayerState)
{
	if (Cast<AWorldPlayerState>(InWorldPlayerState)->GetPawn())
	{
		UBaseWidgetComponent* L_UBaseWidgetComponent = Cast<UBaseWidgetComponent>(Cast<AWorldPlayerState>(InWorldPlayerState)->GetPawn()->
			AddComponentByClass(UBaseWidgetComponent::StaticClass(),
				false,
				FTransform(FRotator::ZeroRotator, FVector::Zero(),
					FVector::One()),
				false));
		L_UBaseWidgetComponent->AssignWidgetToNeedCLass(Cast<AWorldPlayerState>(InWorldPlayerState), GetOwningPlayerController()->GetPlayerState<AWorldPlayerState>());

	}
	else
	{
		Cast<AWorldPlayerState>(InWorldPlayerState)->OnPawnSet.AddUniqueDynamic(this, &APlayerHUD::Bind_CreateWidgetForPlayer);
	}

}

void APlayerHUD::Bind_CreateWidgetForPlayer(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	UBaseWidgetComponent* L_UBaseWidgetComponent = Cast<UBaseWidgetComponent>(NewPawn->
		AddComponentByClass(UBaseWidgetComponent::StaticClass(),
			false,
			FTransform(FRotator::ZeroRotator, FVector::Zero(),
				FVector::One()),
			false));
	L_UBaseWidgetComponent->AssignWidgetToNeedCLass(Cast<AWorldPlayerState>(Player), GetOwningPlayerController()->GetPlayerState<AWorldPlayerState>());

}
