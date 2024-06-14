// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/A_BasePoint.h"
#include "Camera/CameraComponent.h"
#include "Components/AC_CharMove.h"
#include "Core/BasePlayerController.h"
#include "Core/PlayerHUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SpringComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponentActor");
	SpringComponent->SetupAttachment(GetMesh(), FName("head"));
	SpringComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponentActor");
	CameraComponent->SetupAttachment(SpringComponent);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (AllStructInput.StructInput_Q.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_Q.GameplyAbility, 1, INDEX_NONE, this));
		}

		if (AllStructInput.StructInput_E.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_E.GameplyAbility, 1, INDEX_NONE, this));
		}

		if (AllStructInput.StructInput_R.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_R.GameplyAbility, 1, INDEX_NONE, this));
		}
		if (AllStructInput.StructInput_F.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_F.GameplyAbility, 1, INDEX_NONE, this));
		}
		if (AllStructInput.StructInput_T.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_T.GameplyAbility, 1, INDEX_NONE, this));
		}
		if (AllStructInput.StructInput_M.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_M.GameplyAbility, 1, INDEX_NONE, this));
		}
		if (AllStructInput.StructInput_LeftClick.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_LeftClick.GameplyAbility, 1, INDEX_NONE, this));
		}
		if (AllStructInput.StructInput_RightClick.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_RightClick.GameplyAbility, 1, INDEX_NONE, this));
		}
		if (AllStructInput.StructInput_Space.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_Space.GameplyAbility, 1, INDEX_NONE, this));
		}
		if (AllStructInput.StructInput_LCtrl.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_LCtrl.GameplyAbility, 1, INDEX_NONE, this));
		}
		if (AllStructInput.StructInput_LShift.GameplyAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(AllStructInput.StructInput_LShift.GameplyAbility, 1, INDEX_NONE, this));
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* PC = Cast<APlayerController>(GetController());



	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	InputComponent = PlayerInputComponent;

	if (UEnhancedInputComponent* L_UEnhancedInputComponent = PC->GetComponentByClass<UEnhancedInputComponent>())
	{
		L_UEnhancedInputComponent->BindAction(AllStructInput.StructInput_LeftClick.InputAction, ETriggerEvent::Started, this, &ThisClass::Press_LeftClick);
		L_UEnhancedInputComponent->BindAction(AllStructInput.StructInput_LeftClick.InputAction, ETriggerEvent::Completed, this, &ThisClass::Press_LeftClick);

		L_UEnhancedInputComponent->BindAction(AllStructInput.StructInput_LShift.InputAction, ETriggerEvent::Started, this, &ThisClass::Press_Shift);
		L_UEnhancedInputComponent->BindAction(AllStructInput.StructInput_LShift.InputAction, ETriggerEvent::Completed, this, &ThisClass::Press_Shift);

		L_UEnhancedInputComponent->BindAction(AllStructInput.StructInput_Space.InputAction, ETriggerEvent::Started, this, &ThisClass::Press_Space);
		L_UEnhancedInputComponent->BindAction(AllStructInput.StructInput_Space.InputAction, ETriggerEvent::Completed, this, &ThisClass::Press_Space);

		L_UEnhancedInputComponent->BindAction(AllStructInput.StructInput_RightClick.InputAction, ETriggerEvent::Started, this, &ThisClass::Press_RightClick);
		L_UEnhancedInputComponent->BindAction(AllStructInput.StructInput_RightClick.InputAction, ETriggerEvent::Completed, this, &ThisClass::Press_RightClick);

		L_UEnhancedInputComponent->BindAction(AllStructInput.StructInput_R.InputAction, ETriggerEvent::Started, this, &ThisClass::Press_RClick);

	
	}

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ABasePlayerController* L_ABasePlayerController = Cast<ABasePlayerController>(NewController))
	{
		AC_Weapon->Server_CreateWeapon();
	}
}

void APlayerCharacter::UnPossessed()
{
	Super::UnPossessed();

	GetCharacterMovement<UAC_CharMove>()->EndMatch();
	
}

void APlayerCharacter::Press_Shift(const FInputActionValue& Value)
{
	if (IsDie) { return; }
	if (Value.Get<bool>() == true)
	{
		if (AllStructInput.StructInput_LShift.GameplyAbility)
		{
			GetAbilitySystemComponent()->TryActivateAbilityByClass(AllStructInput.StructInput_LShift.GameplyAbility);
		}
	}
	else if (Value.Get<bool>() == false)
	{
		if (AllStructInput.StructInput_LShift.GameplyAbility)
		{
			GetAbilitySystemComponent()->CancelAbility(AllStructInput.StructInput_LShift.GameplyAbility.GetDefaultObject());
		}
	}
}

void APlayerCharacter::Press_LeftClick(const FInputActionValue& Value)
{
	if (IsDie) { return; }
	if (Value.Get<bool>() == true)
	{
		if (AllStructInput.StructInput_LShift.GameplyAbility)
		{
			GetAbilitySystemComponent()->TryActivateAbilityByClass(AllStructInput.StructInput_LeftClick.GameplyAbility);
		}
	}
	else if (Value.Get<bool>() == false)
	{
		if (AllStructInput.StructInput_LShift.GameplyAbility)
		{
			GetAbilitySystemComponent()->CancelAbility(AllStructInput.StructInput_LeftClick.GameplyAbility.GetDefaultObject());
		}
	}
}

void APlayerCharacter::Press_Space(const FInputActionValue& Value)
{
	if (IsDie) { return; }
	if (Value.Get<bool>() == true)
	{
		if (AllStructInput.StructInput_Space.GameplyAbility)
		{
			GetAbilitySystemComponent()->TryActivateAbilityByClass(AllStructInput.StructInput_Space.GameplyAbility);
		}
	}
	else if (Value.Get<bool>() == false)
	{
		if (AllStructInput.StructInput_Space.GameplyAbility)
		{
			GetAbilitySystemComponent()->CancelAbility(AllStructInput.StructInput_Space.GameplyAbility.GetDefaultObject());
		}
	}
}

void APlayerCharacter::Press_RightClick(const FInputActionValue& Value)
{
	if (IsDie) { return; }
	if (Value.Get<bool>() == true)
	{
		if (AllStructInput.StructInput_RightClick.GameplyAbility)
		{
			GetAbilitySystemComponent()->TryActivateAbilityByClass(AllStructInput.StructInput_RightClick.GameplyAbility);
		}
	}
	else if (Value.Get<bool>() == false)
	{
		if (AllStructInput.StructInput_RightClick.GameplyAbility)
		{
			GetAbilitySystemComponent()->CancelAbility(AllStructInput.StructInput_RightClick.GameplyAbility.GetDefaultObject());
		}
	}
}

void APlayerCharacter::Press_RClick(const FInputActionValue& Value)
{
	if (IsDie) { return; }
	if (Value.Get<bool>() == true)
	{
		if (AllStructInput.StructInput_R.GameplyAbility)
		{
			GetAbilitySystemComponent()->TryActivateAbilityByClass(AllStructInput.StructInput_R.GameplyAbility);
		}
	}
	else if (Value.Get<bool>() == false)
	{
		return;
		if (AllStructInput.StructInput_R.GameplyAbility)
		{
			GetAbilitySystemComponent()->CancelAbility(AllStructInput.StructInput_R.GameplyAbility.GetDefaultObject());
		}
	}
}
																										 
void APlayerCharacter::AfterDieCharacter_Player(bool bIsDie)
{
	if (bIsDie == true && IsLocallyControlled())
	{
		Cast<APlayerHUD>(GetLocalViewingPlayerController()->GetHUD())->OnDelegateChangeLayer.Broadcast(0);
	}
	else
	{}
}
