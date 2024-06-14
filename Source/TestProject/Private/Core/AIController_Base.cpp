// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AIController_Base.h"

#include "BrainComponent.h"
#include "Core/WorldGameState.h"
#include "Core/WorldPlayerState.h"
#include "Net/UnrealNetwork.h"

AAIController_Base::AAIController_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	bWantsPlayerState = true;

	bStopAILogicOnUnposses = true;


}

void AAIController_Base::BeginPlay()
{
	Super::BeginPlay();
	Cast<AWorldGameState>(GetWorld()->GetGameState())->OnDelegateEndMatch.AddUniqueDynamic(this, &ThisClass::AAIController_Base::EndGame);
}

void AAIController_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetPawn())
	{
		GetWorld()->GetGameState<AWorldGameState>()->OnDelegateNewPlayer.Broadcast(GetPlayerState<AWorldPlayerState>());
	}
}

void AAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	InPawn->Tags.Find(FName("Team1"))==INDEX_NONE?
	GetPlayerState<AWorldPlayerState>()->Team = 2:
	GetPlayerState<AWorldPlayerState>()->Team = 1;

	GetWorld()->GetGameState<AWorldGameState>()->OnDelegateNewPlayer.Broadcast(GetPlayerState<AWorldPlayerState>());

}

void AAIController_Base::OnUnPossess()
{
	Super::OnUnPossess();
}

void AAIController_Base::Bind_DetectedPawnThisAIController(bool IsDetected)
{
	if (IsDetected)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(TimerDetectedPawn) ||
			GetWorld()->GetTimerManager().IsTimerPaused(TimerDetectedPawn))
		{
			GetWorld()->GetTimerManager().UnPauseTimer(TimerDetectedPawn);
		}
		else
		{
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([ThisControllerAI = MakeShareable(this)]()
				{
					//	ThisControllerAI.Object->OnAIDetectedSignal.Broadcast(false);
				});
			GetWorld()->GetTimerManager().SetTimer(TimerDetectedPawn, TimerDelegate, 10, true, -1);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().PauseTimer(TimerDetectedPawn);
	}
}

void AAIController_Base::Bind_DiePawnController()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerDetectedPawn);
	//	OnAIDetectedSignal.Broadcast(false);
}

void AAIController_Base::EndGame()
{
	UnPossess();
	GetBrainComponent()->StopLogic("all");
	GetBrainComponent()->Deactivate();
	GetBrainComponent()->Cleanup();
}

