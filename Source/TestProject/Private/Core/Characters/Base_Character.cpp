// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/Base_Character.h"

#include "Animation/AnimInstanceProxy.h"
#include "Components/AC_CharMove.h"
#include "Components/CapsuleComponent.h"
#include "Core/BasePlayerController.h"
#include "Core/WorldGameState.h"
#include "Core/WorldPlayerState.h"
#include "GAS/AC_AbilitySystem.h"
#include "GAS/Attributes/Attribute_Health.h"
#include "Net/UnrealNetwork.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

DEFINE_LOG_CATEGORY(LOG_BaseCharacter);

ABase_Character::ABase_Character(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UAC_CharMove>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UAC_AbilitySystem>(this, "AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Attribute_Health = CreateDefaultSubobject<UAttribute_Health>("AttributeHealth");

	AC_Weapon = CreateDefaultSubobject<UAC_Weapon>("AC_Weapon");

	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("AIPerceptionStimuliSourceComponent ");

}


void ABase_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, IsDie);
}

void ABase_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Attribute_Health->SetHealthMax(DefaultHealth);
	Attribute_Health->SetHealth(DefaultHealth);

	Attribute_Health->OnDelegateCurrentHealth.AddUniqueDynamic(this, &ThisClass::Bind_ChangeHealth);

	Attribute_Health->OnDelegateDie.AddUniqueDynamic(this, &ThisClass::Server_DieCharacter_Reliable);

}

void ABase_Character::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocalPlayerControllerViewingAPawn())
	{
		Cast<AWorldGameState>(GetWorld()->GetGameState())->OnDelegateEndMatch.AddUniqueDynamic(this, &ThisClass::Bind_EndGame);
	}

}

void ABase_Character::Bind_ChangeHealth(float CurrentHealthFromAttribute)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::FromInt(static_cast<int>(CurrentHealthFromAttribute)));

	if (CurrentHealthFromAttribute == 0)
	{
		Server_DieCharacter_Reliable();
	}
}

void ABase_Character::Bind_EndGame()
{
	Cast<UAC_CharMove>(GetCharacterMovement())->EndMatch();
	UnPossessed();
}

int ABase_Character::GetTeamCharacter()
{
		return GetPlayerState() ? GetPlayerState<AWorldPlayerState>()->Team : -1;
}


void ABase_Character::Server_Respawn_Reliable_Implementation(FVector LocationForRespawn)
{
	NetMulticast_Respawn_Reliable(LocationForRespawn);
}

void ABase_Character::NetMulticast_Respawn_Reliable_Implementation(FVector LocationForRespawn)
{
	if (!GetCapsuleComponent() || !GetMesh()) { return; }

	SetActorHiddenInGame(true);

	GetMesh()->SetCollisionProfileName("CharacterMesh");
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionProfileName("Pawn");
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	GetMesh()->SetAllBodiesSimulatePhysics(false);

	SetActorLocation(LocationForRespawn + FVector(0, 0, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	IsDie = false;

	Attribute_Health->SetHealth(DefaultHealth);
	Attribute_Health->OnDelegateCurrentHealth.Broadcast(DefaultHealth);

	Attribute_Health->Respawn(DefaultHealth);
	Attribute_Health->OnDelegateRespawn.Broadcast();
	SetActorHiddenInGame(false);
}

void ABase_Character::Server_DieCharacter_Reliable_Implementation()
{
	NetMulticast_DieCharacter_Reliable();
}

void ABase_Character::NetMulticast_DieCharacter_Reliable_Implementation()
{

	IsDie = true;

	if (!GetCapsuleComponent() || !GetMesh()) { return; }


	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetAllBodiesSimulatePhysics(true);

}
