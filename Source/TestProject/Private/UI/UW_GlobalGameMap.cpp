// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_GlobalGameMap.h"

#include "Actors/A_BasePoint.h"
#include "Actors/A_TransportBase.h"	 

#include "Core/Characters/AI_CharBase.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/SizeBox.h"
#include "Core/WorldGameState.h"
#include "Core/WorldPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/UW_BasePoint_IconMap.h"
#include "UI/UW_Pawn_IconMap.h"


void UUW_GlobalGameMap::NativeConstruct()
{
	Super::NativeConstruct();

}

void UUW_GlobalGameMap::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

bool UUW_GlobalGameMap::Initialize()
{
		if(GetWorld()->GetGameState<AWorldGameState>())
		{
			GetWorld()->GetGameState<AWorldGameState>()->OnDelegateNewPlayer.AddUniqueDynamic(this, &UUW_GlobalGameMap::CreateWidgetForNewPlayer);
		}
													 
	return Super::Initialize();
}

void UUW_GlobalGameMap::CreateIconAllControlledPawn()
{
	for (const auto& i : GetWorld()->GetGameState<AWorldGameState>()->PlayerArray)
	{
		if (APawn* L_Pawn = Cast<AWorldPlayerState>(i)->GetPawn())
		{
			UUW_Pawn_IconMap* L_CreatedWidget = Cast<UUW_Pawn_IconMap>(CreateWidget(GetOwningPlayer(), SetTypeUWPawn));

			GridPanelControlledPawn->AddChild(L_CreatedWidget);
			L_CreatedWidget->AssignToOtherPlayerState(Cast<AWorldPlayerState>(i), this);
			UpdateLocationOnTheMap(L_Pawn, L_CreatedWidget);
			UpdateRotationOnTheMap(L_Pawn, L_CreatedWidget);
		}
		else
		{
			UUW_Pawn_IconMap* L_CreatedWidget = Cast<UUW_Pawn_IconMap>(CreateWidget(GetOwningPlayer(), SetTypeUWPawn));
			GridPanelControlledPawn->AddChild(L_CreatedWidget);
			L_CreatedWidget->AssignToOtherPlayerState(Cast<AWorldPlayerState>(i), this);
		}
	}
}



void UUW_GlobalGameMap::CreateIconAllOtherPawn()
{
	TArray<AActor*>AllTransportClassess;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), A_TransportBase::StaticClass(), AllTransportClassess);
	for (auto i : AllTransportClassess)
	{
		UUW_Pawn_IconMap* L_CreatedWidget = Cast<UUW_Pawn_IconMap>(CreateWidget(GetOwningPlayer(), SetTypeUWPawn));

		GridPanelOtherPawn->AddChild(L_CreatedWidget);
		L_CreatedWidget->CreateIconWidget(i);
		L_CreatedWidget->AssignedGlobalGameMap = this;

		UpdateLocationOnTheMap(i, L_CreatedWidget);
		UpdateRotationOnTheMap(i, L_CreatedWidget);

	}
}

void UUW_GlobalGameMap::CreateWidgetForNewPlayer(AWorldPlayerState* WorldPlayerState)
{
	UUW_Pawn_IconMap* L_CreatedWidget = Cast<UUW_Pawn_IconMap>(CreateWidget(GetOwningPlayer(), SetTypeUWPawn));

	GridPanelControlledPawn->AddChild(L_CreatedWidget);

	L_CreatedWidget->AssignToOtherPlayerState(WorldPlayerState, this);


	//CreateComponent
	UBaseWidgetComponent* L_UBaseWidgetComponent = Cast<UBaseWidgetComponent>(WorldPlayerState->GetPawn()->
		AddComponentByClass(UBaseWidgetComponent::StaticClass(),
			false,
			FTransform(FRotator::ZeroRotator, FVector::Zero(),
				FVector::One()),
			false));
																	 
	L_UBaseWidgetComponent->AssignWidgetToNeedCLass(WorldPlayerState, Cast<AWorldPlayerState>(GetOwningPlayerState()));
}

void UUW_GlobalGameMap::CreateIconAllBasePoint()
{
	TArray<AActor*>FindedBasePoint;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePoint::StaticClass(), FindedBasePoint);

	for (const auto& i : FindedBasePoint)
	{
		UUW_BasePoint_IconMap* L_CreatedWidget = Cast<UUW_BasePoint_IconMap>(CreateWidget(GetOwningPlayer(), SetTypeUWBasePoint));
		L_CreatedWidget->NameBasePoint->SetText(FText::FromName(Cast<ABasePoint>(i)->Name));
		L_CreatedWidget->SizeBox->SetWidthOverride(Image->GetBrush().GetImageSize().X / 40);
		L_CreatedWidget->SizeBox->SetHeightOverride(Image->GetBrush().GetImageSize().X / 40);

		L_CreatedWidget->CreateIconWidget(Cast<ABasePoint>(i));

		GridPanelBasePoint->AddChild(L_CreatedWidget);

		// Image size = X we have  Max = X/2 Min = -X/2	 and to with Y
		UpdateLocationOnTheMap(i, L_CreatedWidget);
	}
}



void UUW_GlobalGameMap::UpdateLocationOnTheMap(AActor* AssignedActor, UUserWidget* UUW_Pawn_IconMap)
{
	if (!AssignedActor) { return; }
	if (!UUW_Pawn_IconMap) { return; }
	UUW_Pawn_IconMap->SetRenderTranslation(

		FVector2D(
			UKismetMathLibrary::MapRangeClamped(AssignedActor->GetActorLocation().Y,
				-35000,
				45000,
				Image->GetBrush().GetImageSize().X / 2,
				-Image->GetBrush().GetImageSize().X / 2),

			UKismetMathLibrary::MapRangeClamped(AssignedActor->GetActorLocation().X,
				-40000,
				40000,
				-Image->GetBrush().GetImageSize().Y / 2,
				Image->GetBrush().GetImageSize().Y / 2)));
}

void UUW_GlobalGameMap::UpdateRotationOnTheMap(AActor* AssignedActor, UUserWidget* UUW_Pawn_IconMap)
{
	if (!UUW_Pawn_IconMap || !AssignedActor) { return; }
	
	UUW_Pawn_IconMap->SetRenderTransformAngle(AssignedActor->GetActorRotation().Yaw - 90);
}

