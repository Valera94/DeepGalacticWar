// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "UI/UW_IconMap.h"
#include "UW_BasePoint_IconMap.generated.h"

class AWorldPlayerState;
class USizeBox;
class UButton;

UCLASS(Abstract)
class TESTPROJECT_API UUW_BasePoint_IconMap : public UUW_IconMap
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* NameBasePoint;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UButton* ButtonColorBasePoint;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) USizeBox* SizeBox;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void Bind_IsCapturing(bool isCapturing);

	virtual void CreateIconWidget_Implementation(AActor* InAssignedActor) override;

};
