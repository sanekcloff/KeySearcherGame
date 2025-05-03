// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KSWinGameWidget.generated.h"

class UButton;

UCLASS()
class KEYSEARCHERGAME_API UKSWinGameWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
	void OnRestart();
	UFUNCTION()
	void OnExit();
};
