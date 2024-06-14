// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/A_TransportBase.h"

#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

A_TransportBase::A_TransportBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void A_TransportBase::PostCDOContruct()
{
	Super::PostCDOContruct();
	TransformStartPosition = GetActorTransform();
}

void A_TransportBase::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnAnyDamage);
}

void A_TransportBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	CurrentCyclePawn =1;
}

void A_TransportBase::UnPossessed()
{
	Super::UnPossessed();
	CurrentCyclePawn = 0;
}


void A_TransportBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Health)
	DOREPLIFETIME(ThisClass, CurrentCyclePawn)
}


void A_TransportBase::OnAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health = Health - Damage;
	OnRep_Health();
}

void A_TransportBase::OnRep_Health()
{
	if (Health <= 0)
	{
		CurrentCyclePawn = 2;
		OnRep_CurrentCyclePawn();
	}
	//ToDo We Can add logic visual 
}

void A_TransportBase::OnRep_CurrentCyclePawn()
{
	if(CurrentCyclePawn == 0)
	{
		OnCurrentStatusPawn.Broadcast(0);
		Health = 100;
		OnRep_Health();
		SetActorHiddenInGame(false);

	}
	else if(CurrentCyclePawn ==1)
	{
		OnCurrentStatusPawn.Broadcast(1);

	}
	else if(CurrentCyclePawn == 2)
	{
		OnCurrentStatusPawn.Broadcast(2);

		SetActorHiddenInGame(true);

		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this,&A_TransportBase::OnRep_CurrentCyclePawn);

		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false, TimeForResurrection);
		CurrentCyclePawn = 0;
	}
}
