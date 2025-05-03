// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KSPlayerHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class KEYSEARCHERGAME_API UKSPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetGameSecondsRemaining() const;
};
