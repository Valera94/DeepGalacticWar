// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "A_BasePoint.generated.h"


class UWidgetComponent;
class USceneCaptureComponent2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegateChangeTeam, int, CurrentTeam);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegateCurrentPercentBasePoint, float, CurrentPercentCaptureBasePoint);


UCLASS()
class TESTPROJECT_API ABasePoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePoint();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//------- Delegates ---------//

	UPROPERTY(BlueprintAssignable) FBPDelegateCurrentPercentBasePoint OnDelegateCurrentPercentBasePoint;
	


	UFUNCTION() void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION() void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//--------------------------//

#pragma region |---Default---|

	// *Component for Detect overlapped and try capture if bCanBeCapture == true;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "DefaultComponent")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	// *It Can be Flag or Base and etc... It Can be animate.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "DefaultComponent")
	TObjectPtr<UChildActorComponent> ChildActorComponent;
	// *Camera component for view on MiniMap
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "DefaultComponent")
	TObjectPtr<USceneComponent> CameraAttach;
	// *Widget Component Show only 1 local player
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "DefaultComponent")
	TObjectPtr<UWidgetComponent> WidgetComponent;
	// *This  Component used how root for spawn character
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "DefaultComponent")
	TObjectPtr<USceneComponent> SceneComponentForSpawn;

#pragma endregion



	/* Change Team */
	UPROPERTY(BlueprintAssignable)FBPDelegateChangeTeam OnDelegateChangeTeam;
	UFUNCTION()void OnRepTeam();
	//0 = Neutral 1 = TeamA 2 = TeamB;
	UPROPERTY(ReplicatedUsing = OnRepTeam, BlueprintReadWrite, EditAnywhere, Category = "SettingBasePoint")
	int Team = 0;
	




	UPROPERTY(BlueprintReadOnly) int OverlappedTeamA = 0;
	UPROPERTY(BlueprintReadOnly) int OverlappedTeamB = 0;

	UFUNCTION(BlueprintCallable,BlueprintPure) bool IsCapturedBasePoint(const int InTeam);
																											  
	//	Name this base point;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SettingBasePoint")FName Name = "A";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SettingBasePoint")bool bCanBeCaptured = false;

	//Get Random position for spawn;
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "BasePoint")
	FTransform GetPositionForSpawnCharacter();

	UFUNCTION(BlueprintCallable)
	void UpdatePercentCapture();
														 

protected:

	//	Team Empty = 1.5; Team A = 0; Team B = 3;
	UPROPERTY(ReplicatedUsing = OnRep_CurrentPercentCapturePoint, BlueprintReadOnly)
	float CurrentPercentCapturePoint;
	UFUNCTION()void OnRep_CurrentPercentCapturePoint();

//public:
//	UFUNCTION(Server,Reliable,Category="Command")
//	void Server_BasePoint_ChangeTeam(FName SetNameBasePoint, int SetTeam_0Empty_1A_2B);
};
