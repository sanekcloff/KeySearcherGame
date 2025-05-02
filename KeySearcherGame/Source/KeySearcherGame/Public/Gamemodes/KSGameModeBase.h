// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KSGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class KEYSEARCHERGAME_API AKSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AKSGameModeBase();
	UFUNCTION(BlueprintCallable)
	int32 GetKeysCollected() const { return KeysCollected; }

	UFUNCTION(BlueprintCallable)
	int32 GetKeyFinish() const { return KeysFinish; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamemode Rules")
	TSubclassOf<AActor> KeyActor;

	virtual void StartPlay() override;

private:
	int32 KeysCollected = 0;
	int32 KeysFinish = 0;

	void InitKeyFinishCount();
};
