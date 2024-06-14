// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WorldPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateDeath, int, CurrentDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateKill, int, CurrentKill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateAssist, int, CurrentAssist);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegatePoints, int, CurrentPoints);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTeam, int, CurrentTeam);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateIsDetected, bool, CurrentIsDetected);


UCLASS()
class TESTPROJECT_API AWorldPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	AWorldPlayerState();
	virtual void OnRep_Owner() override;
	virtual void BeginPlay() override;
																				 
	UPROPERTY(BLueprintAssignable) FDelegateDeath OnDelegateDeath;
	UFUNCTION()void OnRepDeath() const { OnDelegateDeath.Broadcast(Death); }
	UPROPERTY(ReplicatedUsing = OnRepDeath, BlueprintReadWrite, EditAnywhere, Transient, Category = "InformationPlayer")
	int Death = 0;

	UPROPERTY(BLueprintAssignable) FDelegateKill OnDelegateKill;
	UFUNCTION()void OnRepKill() const { OnDelegateKill.Broadcast(Kill); }
	UPROPERTY(ReplicatedUsing = OnRepKill, BlueprintReadWrite, EditAnywhere, Transient, Category = "InformationPlayer")
	int Kill = 0;

	UPROPERTY(BLueprintAssignable) FDelegateAssist OnDelegateAssist;
	UFUNCTION()void OnRepAssist() const { OnDelegateAssist.Broadcast(Assist); }
	UPROPERTY(ReplicatedUsing = OnRepAssist, BlueprintReadWrite, EditAnywhere, Transient, Category = "InformationPlayer")
	int Assist = 0;

	UPROPERTY(BLueprintAssignable) FDelegatePoints OnDelegatePoints;
	UFUNCTION()void OnRepPoints() const { OnDelegatePoints.Broadcast(Points); }
	UPROPERTY(ReplicatedUsing = OnRepPoints, BlueprintReadWrite, EditAnywhere, Transient, Category = "InformationPlayer")
	int Points = 0;

	UPROPERTY(BLueprintAssignable) FDelegateTeam OnDelegateTeam;
	UFUNCTION()void OnRepTeam() const { OnDelegateTeam.Broadcast(Team); }
	//0-None,1-TeamA,2-TeamB
	UPROPERTY(ReplicatedUsing = OnRepTeam, BlueprintReadWrite, EditAnywhere, Transient, Category = "InformationPlayer")
	int Team = -1;

	UFUNCTION(BlueprintCallable) void Activate_IsDetected(bool IsDetected);
	UPROPERTY(BLueprintAssignable) FDelegateIsDetected OnDelegateIsDetected;
	UFUNCTION()void OnRepIsDetected() const { OnDelegateIsDetected.Broadcast(bIsDetected); }
	UPROPERTY(ReplicatedUsing = OnRepIsDetected, BlueprintReadWrite, EditAnywhere, Transient, Category = "InformationPlayer")
	bool bIsDetected = false;

	//0-Neutral, 1-Friend,2-Enemy
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerState")
	int GetTeamResult(const int OtherTeam) const;
};
