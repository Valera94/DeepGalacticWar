// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/A_BasePoint.h"

#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Core/BasePlayerController.h"
#include "Core/PlayerHUD.h"
#include "Core/WorldGameState.h"
#include "Core/WorldPlayerState.h"
#include "Core/Characters/Base_Character.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABasePoint::ABasePoint()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(1);

	// *Component for Detect overlapped and try capture if bCanBeCapture == true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->SetupAttachment(GetRootComponent());
	CapsuleComponent->SetHiddenInGame(false);

	// *It Can be Flag or Base and etc... It Can be animate.
	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>("ChildActorComponent");
	ChildActorComponent->SetupAttachment(CapsuleComponent);

	SceneComponentForSpawn = CreateDefaultSubobject<USceneComponent>("SceneComponentForSpawn");
	SceneComponentForSpawn->SetupAttachment(CapsuleComponent);

	CameraAttach = CreateDefaultSubobject<USceneComponent>("CameraAttach");
	CameraAttach->SetupAttachment(CapsuleComponent);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(CapsuleComponent);



	if (bCanBeCaptured == false)
	{
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void ABasePoint::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	if (bCanBeCaptured == false)
	{
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}


	if (Team == 0)
	{
		CurrentPercentCapturePoint = 1.5;
	}
	else if (Team == 1)
	{
		CurrentPercentCapturePoint = 0;
	}
	else if (Team == 2)
	{
		CurrentPercentCapturePoint = 3;
	}

	OnDelegateCurrentPercentBasePoint.Broadcast(CurrentPercentCapturePoint);
	OnRep_CurrentPercentCapturePoint();

	if (HasAuthority())
	{
		CapsuleComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABasePoint::BeginOverlap);
		CapsuleComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ABasePoint::EndOverlap);
	}
}

void ABasePoint::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdatePercentCapture();
}


void ABasePoint::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Team);
	DOREPLIFETIME(ThisClass, CurrentPercentCapturePoint);

}

void ABasePoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (!HasAuthority() || bCanBeCaptured == false) { return; }


	if (const AWorldPlayerState* L_AWorldPlayerState = Cast<AWorldPlayerState>(Cast<APawn>(OtherActor)->GetPlayerState()))
	{
		if (L_AWorldPlayerState->Team != 0)
		{
			if (L_AWorldPlayerState->Team == 1)
			{
				OverlappedTeamA++;

				if (OverlappedTeamA != OverlappedTeamB)
				{
					if (!IsActorTickEnabled()) { SetActorTickEnabled(true); }
				}
			}
			else
			{
				OverlappedTeamB++;

				if (OverlappedTeamA != OverlappedTeamB)
				{
					if (!IsActorTickEnabled()) { SetActorTickEnabled(true); }
				}
			}
		}

	}
}

void ABasePoint::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!HasAuthority() || bCanBeCaptured == false) { return; }


	if (const AWorldPlayerState* L_AWorldPlayerState = Cast<AWorldPlayerState>(Cast<APawn>(OtherActor)->GetPlayerState()))
	{
		if (L_AWorldPlayerState->Team != 0)
		{
			if (L_AWorldPlayerState->Team == 1)
			{
				OverlappedTeamA--;
			}
			else
			{
				OverlappedTeamB--;
			}
		}

	}

	if (OverlappedTeamA == OverlappedTeamB)
	{
		SetActorTickEnabled(false);
		return;
	}

}


void ABasePoint::OnRep_CurrentPercentCapturePoint()
{
	OnDelegateCurrentPercentBasePoint.Broadcast(Team);
}




void ABasePoint::UpdatePercentCapture()
{
	if (!HasAuthority()) { return; }
	if (OverlappedTeamA == OverlappedTeamB) { return; }


	//1 = TeamA		0
	//0 = Neutral	1.5
	//2 = TeamB		3
	const int AbsChange = OverlappedTeamA - OverlappedTeamB;
	CurrentPercentCapturePoint = FMath::Clamp(CurrentPercentCapturePoint - (AbsChange * 0.5), 0, 3);

	OnDelegateCurrentPercentBasePoint.Broadcast(CurrentPercentCapturePoint);
	OnRep_CurrentPercentCapturePoint();

	//1 = TeamA		0
	//0 = Neutral	1.5
	//2 = TeamB		3

	//Set Team
	if (CurrentPercentCapturePoint == 0)
	{
		Team = 1;

		OnDelegateChangeTeam.Broadcast(Team);
		OnRepTeam();
	}
	else if (CurrentPercentCapturePoint == 1.5)
	{
		Team = 0;

		OnDelegateChangeTeam.Broadcast(Team);
		OnRepTeam();
	}
	else if (CurrentPercentCapturePoint == 3)
	{
		Team = 2;

		OnDelegateChangeTeam.Broadcast(Team);
		OnRepTeam();
	}

	return;

}


void ABasePoint::OnRepTeam()
{
	OnDelegateChangeTeam.Broadcast(Team);
}

bool ABasePoint::IsCapturedBasePoint(const int InTeam)
{
	if (InTeam == 1) { return OverlappedTeamB != 0; }
	else if (InTeam == 2) { return OverlappedTeamA != 0; }
	return false;
}

FTransform ABasePoint::GetPositionForSpawnCharacter()
{

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Camera));
	TArray<AActor*>Ignore;
	FHitResult HitResult;

	for (const auto& i : SceneComponentForSpawn->GetAttachChildren())
	{
		if (UKismetSystemLibrary::CapsuleTraceSingle(
			GetWorld(),
			i->GetComponentLocation() + FVector(0, 0, 90 * 4),
			i->GetComponentLocation() + FVector(0, 0, 120),
			45.f,
			90.f, ETraceTypeQuery::TraceTypeQuery_MAX, false, Ignore, EDrawDebugTrace::ForDuration, HitResult, false
		) == false)
		{

			return i->GetComponentTransform() + FTransform(FRotator::ZeroRotator, FVector(0, 0, 90), FVector::One());
		}

	}

	return FTransform(GetActorTransform().GetRotation(), GetActorTransform().GetLocation(), FVector::One());
}

//void ABasePoint::Server_BasePoint_ChangeTeam_Implementation(FName SetNameBasePoint, int SetTeam_0Empty_1A_2B)
//{
//	if (SetNameBasePoint != Name) { return; }
//
//	if (SetTeam_0Empty_1A_2B == 0)
//	{
//		CurrentPercentCapturePoint = 1.5;
//	}
//	else if (SetTeam_0Empty_1A_2B == 2)
//	{
//		CurrentPercentCapturePoint = 3;
//	}
//	else if (SetTeam_0Empty_1A_2B == 1)
//	{
//		CurrentPercentCapturePoint = 0;
//	}
//	Team = SetTeam_0Empty_1A_2B;
//	OnDelegateChangeTeam.Broadcast(Team);
//	OnRepTeam();
//}