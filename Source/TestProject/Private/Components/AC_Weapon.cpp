// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AC_Weapon.h"

#include "Camera/CameraComponent.h"
#include "Core/Characters/Base_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

UAC_Weapon::UAC_Weapon()
{
}

void UAC_Weapon::InitializeComponent()
{
	Super::InitializeComponent();

	SetIsReplicated(true);
	SetComponentTickEnabled(false);
}

void UAC_Weapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentWeapon);
}

void UAC_Weapon::Server_CreateWeapon_Implementation()
{

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.bNoFail = true;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ActorSpawnParameters.Owner = Cast<ABase_Character>(GetOwner());

	AA_Weapon* L_AA_Weapon = GetWorld()->SpawnActor<AA_Weapon>(
		Weapon,
		Cast<ACharacter>(GetOwner())->GetMesh()->GetSocketTransform("Gun_Socket"),
		ActorSpawnParameters);

	L_AA_Weapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Gun_Socket");

	CurrentWeapon = L_AA_Weapon;

}
																																									 