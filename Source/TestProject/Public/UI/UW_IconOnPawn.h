// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "UW_IconOnPawn.generated.h"

class AWorldPlayerState;

UCLASS()
class TESTPROJECT_API UUW_IconOnPawn : public UUserWidget
{
	GENERATED_BODY()

public:

	 virtual bool Initialize() override;
	

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) UImage* ImagePawn;

	UFUNCTION()void AssignToWorldPlayerState(AWorldPlayerState* OtherWorldPlayerState, AWorldPlayerState* OwnerPlayerState);


	UFUNCTION(BlueprintNativeEvent,BlueprintCallable) void Bind_Detected(const bool IsDetected);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable) void Bind_Die();
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable) void Bind_Respawn();
	//0-Neutral,1-Friend,2-Enemy,3-Self
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable) void Bind_Team(int CurrentTeam);
};

