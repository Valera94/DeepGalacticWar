// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Core/Characters/Base_Character.h"
#include "PlayerCharacter.generated.h"

#pragma region |--Structura--|

USTRUCT(BlueprintType)
struct FStructInputWithAbility
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)	UInputAction* InputAction;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)	TSubclassOf<UGameplayAbility> GameplyAbility;

};

USTRUCT(BlueprintType)
struct FAllStructInput
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_Q;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_E;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_R;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_F;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_T;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_M;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_LeftClick;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_RightClick;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_Space;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_LCtrl;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)FStructInputWithAbility StructInput_LShift;


};

#pragma endregion

UCLASS()
class TESTPROJECT_API APlayerCharacter : public ABase_Character
{
	GENERATED_BODY()

	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
	void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess)) TObjectPtr<USpringArmComponent> SpringComponent;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess)) TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditDefaultsOnly)class UInputMappingContext* InputMapping;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess)) FAllStructInput AllStructInput;


public:
	UFUNCTION()void Press_Shift(const FInputActionValue& Value);
	UFUNCTION()void Press_LeftClick(const FInputActionValue& Value);
	UFUNCTION()void Press_Space(const FInputActionValue& Value);
	UFUNCTION()void Press_RightClick(const FInputActionValue& Value);
	UFUNCTION()void Press_RClick(const FInputActionValue& Value);

	UFUNCTION() void AfterDieCharacter_Player(bool bIsDie);
};
