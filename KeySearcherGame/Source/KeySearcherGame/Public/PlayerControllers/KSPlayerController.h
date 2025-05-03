// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KSCoreTypes.h"
#include "KSPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class KEYSEARCHERGAME_API AKSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	UInputAction* PauseAction;

	virtual void SetupInputComponent() override;
private:
	void OnMatchStateChanged(EKSMatchState State);
	void OnPauseGame();
};
