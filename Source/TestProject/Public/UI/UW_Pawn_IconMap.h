// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_IconMap.h"
#include "UW_Pawn_IconMap.generated.h"

class AAIController_Base;
/**
 *
 */
UCLASS(Abstract)
class TESTPROJECT_API UUW_Pawn_IconMap : public UUW_IconMap
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void Bind_DetectedController(const bool IsDetected);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void Bind_Die();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void Bind_Respawn();

	UFUNCTION(BlueprintCallable) void CalculateTeamResultPawn(const int Team);
	UFUNCTION() void Bind_OnPawnSet(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)void AssignToOtherPlayerState(AWorldPlayerState* State, UUW_GlobalGameMap* GlobalGameMap);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	UUW_GlobalGameMap* AssignedGlobalGameMap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	AWorldPlayerState* AssignedPlayerState;

};
