// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseWidgetComponent.h"

#include "Core/WorldGameState.h"
#include "Core/WorldPlayerState.h"
#include "UI/UW_IconOnPawn.h"


UBaseWidgetComponent::UBaseWidgetComponent()
{
	static ConstructorHelpers::FClassFinder<UUW_IconOnPawn> UserWidgetObject(TEXT("WidgetBlueprint'/Game/Game/UI/PawnInfo/UW_OnPawn.UW_OnPawn_C'"));
	if (UserWidgetObject.Succeeded())
	{
		SetWidgetClass(UserWidgetObject.Class);
	}

	check(GetWidgetClass())

	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawSize(FVector2D(0.0125, 0.0125));
	SetDrawAtDesiredSize(true);
}

void UBaseWidgetComponent::InitWidget()
{
	Super::InitWidget();



}

void UBaseWidgetComponent::AssignWidgetToNeedCLass(AWorldPlayerState* OtherWorldPlayerState, AWorldPlayerState* OwnerPlayerState)
{
	if (!OtherWorldPlayerState || !OwnerPlayerState) { return; }

	AssignedWorldPlayerStateAttached = OtherWorldPlayerState;
	OwnerWorldPlayerState = OwnerPlayerState;

	OtherWorldPlayerState->OnPawnSet.AddUniqueDynamic(this, &ThisClass::Bind_Pawn);
	OtherWorldPlayerState->OnDelegateTeam.AddUniqueDynamic(this, &ThisClass::Bind_Team);

}

void UBaseWidgetComponent::Bind_Pawn(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	if (!NewPawn) { return; }

	AttachToComponent(NewPawn->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void UBaseWidgetComponent::Bind_Team(const int Team)
{
	Cast<UUW_IconOnPawn>(GetWidget())->AssignToWorldPlayerState(
		AssignedWorldPlayerStateAttached,
		OwnerWorldPlayerState);
}

void UBaseWidgetComponent::OnAttachmentChanged()
{
	Super::OnAttachmentChanged();

	SetRelativeTransform(FTransform(FRotator::ZeroRotator, FVector(0, 0, 90), FVector::One()));
}
