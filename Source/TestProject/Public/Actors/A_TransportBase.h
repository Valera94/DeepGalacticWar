// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UI/UW_Pawn_IconMap.h"
#include "A_TransportBase.generated.h"

class UBoxComponent;
// 0-wait , 1-Possessed, 2-Destroy
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentStatusPawn, int, Status);

UCLASS()
class TESTPROJECT_API A_TransportBase : public ACharacter
{
	GENERATED_BODY()

public:
	A_TransportBase();
	virtual void PostCDOContruct() override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	/*  *Delegate  */
	UPROPERTY(BlueprintAssignable) FCurrentStatusPawn OnCurrentStatusPawn;// 0-wait , 1-Possessed, 2-Destroy
	/*------------*/

	UPROPERTY(BlueprintReadWrite,EditAnywhere) float TimeForResurrection = 5;
	// This transform used how start position for recreate pawn.
	UPROPERTY(BlueprintReadOnly) FTransform TransformStartPosition; 


	UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing = OnRep_Health) int Health=100;
	UFUNCTION()void OnRep_Health();


	// 0-wait , 1-Possessed, 2-Destroy
	UPROPERTY(ReplicatedUsing = OnRep_CurrentCyclePawn) int CurrentCyclePawn;
	UFUNCTION() void OnRep_CurrentCyclePawn();
	



};
