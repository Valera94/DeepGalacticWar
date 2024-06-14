// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Interfaces/RepresentativeWidget.h"
#include "UW_GlobalGameMap.generated.h"


class AWorldPlayerState;
class UScaleBox;
class UImage;
class UOverlay;
class UUW_BasePoint_IconMap;
class UUW_Pawn_IconMap;
class UUW_IconMap;

//0-WaitDeploy, 1-PawnView,2-TableStatics,3-OpenMap
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangeModeView, int, ChangeModeView);

UCLASS(Abstract)
class TESTPROJECT_API UUW_GlobalGameMap : public UUserWidget, public IRepresentativeWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual bool Initialize() override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable) FDelegateChangeModeView OnDelegateChangeModeView;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool bUseMiniMap = false;


	UPROPERTY(meta = (BindWidget)) UGridPanel* GridPanelBasePoint;		//All Actors BasePoint;
	UPROPERTY(meta = (BindWidget)) UGridPanel* GridPanelOtherPawn;		//All units who wait possess;
	UPROPERTY(meta = (BindWidget)) UGridPanel* GridPanelControlledPawn;	//All units who controlled AIController or Player Friend team;
	UPROPERTY(meta = (BindWidget)) UGridPanel* GridPanelEnemy;			//All units who controlled AIController or Player Enemy command;
	UPROPERTY(meta = (BindWidget)) UImage* Image;						//Image Map game;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|SetUW")TSubclassOf<UUW_Pawn_IconMap> SetTypeUWPawn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|SetUW")TSubclassOf<UUW_BasePoint_IconMap> SetTypeUWBasePoint;

	UFUNCTION(BlueprintCallable)void CreateIconAllControlledPawn();		//All units who controlled AIController or Player;
	UFUNCTION(BlueprintCallable)void CreateIconAllOtherPawn();			//All units who wait possess;
	UFUNCTION(BlueprintCallable)void CreateIconAllBasePoint();			//All Actors BasePoint;

	UFUNCTION(BlueprintCallable)void CreateWidgetForNewPlayer(AWorldPlayerState* WorldPlayerState);
	
	UFUNCTION(BlueprintCallable)void UpdateLocationOnTheMap(AActor* AssignedActor, UUserWidget* UUW_Pawn_IconMap);
	UFUNCTION(BlueprintCallable)void UpdateRotationOnTheMap(AActor* AssignedActor, UUserWidget* UUW_Pawn_IconMap);

};
