// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KSCoreTypes.h"
#include "KSGameModeBase.generated.h"


UCLASS()
class KEYSEARCHERGAME_API AKSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AKSGameModeBase();

	FOnMatchStateChangedSignature OnMatchStateChanged;

	UFUNCTION(BlueprintCallable)
	int32 GetKeysCollected() const { return KeysCollected; }

	UFUNCTION(BlueprintCallable)
	int32 GetKeyFinish() const { return KeysFinish; }

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;
	UFUNCTION(BlueprintCallable)
	int32 GetGameSecondsRemaining() const { return GameCountDown; }


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamemode Rules")
	TSubclassOf<AActor> KeyActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamemode Rules")
	int32 GameCountDown = 180;

	virtual void StartPlay() override;
	UFUNCTION(BlueprintCallable)
	void CollectKey();

private:
	int32 KeysCollected = 0;
	int32 KeysFinish = 0;
	EKSMatchState MatchState = EKSMatchState::WaitingtoStart;
	FTimerHandle GamerTimerHandle;

	void InitKeyFinishCount();
	void SetMatchState(EKSMatchState State);
	void GetTimerUpdate();
	void GameOver();
	void WinGame();
};
