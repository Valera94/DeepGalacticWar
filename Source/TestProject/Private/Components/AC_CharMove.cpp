// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AC_CharMove.h"

#include "Core/WorldGameState.h"

#pragma region /* ChangeRotateLook */


void UAC_CharMove::BeginPlay()
{
	Super::BeginPlay();

	if (GetCharacterOwner()->IsLocalPlayerControllerViewingAPawn())
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([this]()
			{
				ChangeControlRotate();
			});

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.05, true, -1);
	}
}


void UAC_CharMove::ChangeControlRotate()
{
	if (GetNetMode() == ENetMode::NM_Standalone)
	{
		OnDelegateRotateLook.Broadcast(GetCalculatePitchControlRotation());
	}
	else
	{
		if (GetOwnerRole() == ENetRole::ROLE_Authority && GetCharacterOwner()->GetLocalViewingPlayerController())
		{
			NetMulticast_ControlRotationThisCharacter_Unreliable(GetCalculatePitchControlRotation());
		}
		else
		{
			Server_ControlRotationThisCharacter_Unreliable(GetCalculatePitchControlRotation());
		}
	}
}


void UAC_CharMove::Server_ControlRotationThisCharacter_Unreliable_Implementation(float NewRotateLook)
{
	NetMulticast_ControlRotationThisCharacter_Unreliable(NewRotateLook);
}

void UAC_CharMove::NetMulticast_ControlRotationThisCharacter_Unreliable_Implementation(float NewRotateLook)
{
	OnDelegateRotateLook.Broadcast(NewRotateLook);
}
#pragma endregion


void UAC_CharMove::ChangeAim(bool IsAim)
{
	OnDelegateChangeAim.Broadcast(IsAim);
	if (GetOwnerRole() == ENetRole::ROLE_Authority)
	{
		//bIsAim = IsAim;
		NetMulticast_ChangeAim_Unreliable(IsAim);
	}
	else
	{
		Server_ChangeAim_Unreliable(IsAim);
	}


}

void UAC_CharMove::EndMatch()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UAC_CharMove::Server_ChangeAim_Unreliable_Implementation(bool IsAim)
{
	//bIsAim = IsAim;
	NetMulticast_ChangeAim_Unreliable(IsAim);
}

void UAC_CharMove::NetMulticast_ChangeAim_Unreliable_Implementation(bool IsAim)
{
	MaxWalkSpeed = IsAim ? 150 : 450;
	OnDelegateChangeAim.Broadcast(IsAim);
}

