// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/A_Weapon.h"

#include "Camera/CameraComponent.h"
#include "Components/AC_CharMove.h"
#include "Core/Characters/Base_Character.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/SpringArmComponent.h"

AA_Weapon::AA_Weapon()
{
	SetActorTickEnabled(false);

	bReplicates = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(SkeletalMeshComponent);
}
void AA_Weapon::BeginPlay()
{
	Super::BeginPlay();


}

void AA_Weapon::SetAim(bool IsAim)
{

	if (IsAim == true)
	{
		Cast<UCameraComponent>(GetAttachParentActor()->GetComponentByClass(UCameraComponent::StaticClass()))->AttachToComponent(
			SkeletalMeshComponent,
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			"Aim_Socket");

		GetAttachParentActor()->GetComponentByClass<UAC_CharMove>()->ChangeAim(IsAim);
	}
	else
	{
		Cast<UCameraComponent>(GetAttachParentActor()->GetComponentByClass(UCameraComponent::StaticClass()))->AttachToComponent(
			Cast<USpringArmComponent>(GetAttachParentActor()->GetComponentByClass(USpringArmComponent::StaticClass())),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		GetAttachParentActor()->GetComponentByClass<UAC_CharMove>()->ChangeAim(IsAim);
	}

}

void AA_Weapon::SendMessage_Implementation(int SetCurrent_AmmoInClip, int SetCurrent_TotalAmmo)
{
	OnDelegateCurrentAmmoInClip.Broadcast(SetCurrent_AmmoInClip);
	OnDelegateCurrentTotalAmmo.Broadcast(SetCurrent_TotalAmmo);
}

void AA_Weapon::Server_Shoot_Implementation()
{
	Current_AmmoInClip = Current_AmmoInClip - CostOfOneShot;
	SendMessage(Current_AmmoInClip, Current_TotalAmmo);
}



void AA_Weapon::Server_Reload_Implementation()
{
	if (Current_TotalAmmo <= 0 || Current_AmmoInClip == Max_AmmoInClip) { return; }

	const int HowMuchCanAddAmmo = FMath::Min(Max_AmmoInClip - Current_AmmoInClip, Current_TotalAmmo);

	Current_TotalAmmo = Current_TotalAmmo - HowMuchCanAddAmmo;
	Current_AmmoInClip = Current_AmmoInClip + HowMuchCanAddAmmo;

	SendMessage(Current_AmmoInClip, Current_TotalAmmo);

}

FHitResult AA_Weapon::GetHitResultWeapon()
{
	FHitResult HitResult;
	FVector StartTrace = SkeletalMeshComponent->GetSocketTransform("Muzzle_Socket").GetLocation();
	FVector EndTrace = SkeletalMeshComponent->GetSocketTransform("Muzzle_Socket").GetLocation() +
		SkeletalMeshComponent->GetSocketTransform("Muzzle_Socket").GetRotation().GetForwardVector() * 20000;


	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Camera, QueryParams);

	return HitResult;
}

FHitResult AA_Weapon::GetHitResultWeapon_AI()
{
	FHitResult HitResult;
	FVector StartTrace = SkeletalMeshComponent->GetSocketTransform("Muzzle_Socket").GetLocation();

	FVector EndTrace = Cast<ACharacter>(GetAttachParentActor())->GetActorLocation() + FVector(0, 0, 45) +
		Cast<ACharacter>(GetAttachParentActor())->GetActorRotation().GetComponentForAxis(EAxis::X) * 20000;

	//SkeletalMeshComponent->GetSocketTransform("Muzzle_Socket").GetLocation() +
		//SkeletalMeshComponent->GetSocketTransform("Muzzle_Socket").GetRotation().GetForwardVector() * 20000;


	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Camera, QueryParams);

	return HitResult;
}

void AA_Weapon::IsDieAttachParent(bool IsDie)
{
	if (!IsDie)
	{
		Current_AmmoInClip = Max_AmmoInClip;
		Current_TotalAmmo = Max_TotalAmmo;

		SendMessage(Current_AmmoInClip, Current_TotalAmmo);

	}
}


void AA_Weapon::ChangeTypeShot(const FInputActionValue& Value)
{
	switch (CurrentTypeShot)
	{
	case ETypeShot::SingleShot:

		if (SequenceShot == true)
		{
			CurrentTypeShot = ETypeShot::SequenceShot;
		}
		else if (MultiplyShot == true)
		{
			CurrentTypeShot = ETypeShot::MultiplyShot;
		}
		break;

	case ETypeShot::SequenceShot:

		if (MultiplyShot == true)
		{
			CurrentTypeShot = ETypeShot::MultiplyShot;
		}
		else if (SingleShot == true)
		{
			CurrentTypeShot = ETypeShot::SingleShot;
		}
		break;

	case ETypeShot::MultiplyShot:
		if (SingleShot == true)
		{
			CurrentTypeShot = ETypeShot::SingleShot;
		}
		else if (SequenceShot == true)
		{
			CurrentTypeShot = ETypeShot::SequenceShot;
		}
		break;
	}

	OnDelegateChangedTypeShot.Broadcast(CurrentTypeShot);
}



bool AA_Weapon::IsEmptyAmmoInClip()
{
	return Current_AmmoInClip <= 0;
}
