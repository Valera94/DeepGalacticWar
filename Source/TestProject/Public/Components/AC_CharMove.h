// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AC_CharMove.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangeRotateLook, float, RotateLook);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangeCrouch, bool, bIsPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangeAim, bool, bIsPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangeSpeed, float, CurrentSpeed);


UCLASS()
class TESTPROJECT_API UAC_CharMove : public UCharacterMovementComponent
{
	GENERATED_BODY()


	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable) void ChangeControlRotate();
	UFUNCTION(Server, Unreliable) void Server_ControlRotationThisCharacter_Unreliable(float NewRotateLook);
	UFUNCTION(NetMulticast, Unreliable) void NetMulticast_ControlRotationThisCharacter_Unreliable(float NewRotateLook);

	UFUNCTION(BlueprintCallable) float GetCalculatePitchControlRotation() const
	{
		if (const ACharacter* L_Character = Cast<ACharacter>(GetCharacterOwner()))
		{
			const float A = 360 - L_Character->GetControlRotation().Pitch;
			const float B = L_Character->GetControlRotation().Pitch * -1;
			return L_Character->GetControlRotation().Pitch > 180 ? A : B;
		}
		return 0;
	};

public:
	UFUNCTION(BlueprintCallable)void ChangeAim(bool IsAim);
	UFUNCTION()void EndMatch();
	UPROPERTY()	FTimerHandle TimerHandle;

private:
	UFUNCTION(Server, Unreliable)void Server_ChangeAim_Unreliable(bool IsAim);
	UFUNCTION(NetMulticast, Unreliable)void NetMulticast_ChangeAim_Unreliable(bool IsAim);

	



#pragma region /* ChangeCrouch */
protected:
	/* Simple broadcast Delegate */
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
	{
		OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust); OnDelegateChangeCrouch.Broadcast(true);
	}
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
	{
		OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust); OnDelegateChangeCrouch.Broadcast(false);
	}


#pragma endregion

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateChangeRotateLook	OnDelegateRotateLook;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateChangeCrouch		OnDelegateChangeCrouch;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateChangeSpeed		OnDelegateChangeSpeed;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)FDelegateChangeAim			OnDelegateChangeAim;
	
};
