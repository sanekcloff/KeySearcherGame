// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/KSGameModeBase.h"
#include "Characters/KSBaseCharacter.h"
#include "PlayerControllers/KSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "UI/Huds/KSGameHUD.h"
#include "EngineUtils.h"

AKSGameModeBase::AKSGameModeBase()
{
	DefaultPawnClass = AKSBaseCharacter::StaticClass();
	PlayerControllerClass = AKSPlayerController::StaticClass();
	HUDClass = AKSGameHUD::StaticClass();
}

void AKSGameModeBase::StartPlay()
{
	Super::StartPlay();
	InitKeyFinishCount();
	SetMatchState(EKSMatchState::InProgress);
	GetWorldTimerManager().SetTimer(GamerTimerHandle, this, &AKSGameModeBase::GetTimerUpdate, 1.0f, true);
}

void AKSGameModeBase::CollectKey()
{
	KeysCollected++;

	if (KeysCollected == KeysFinish) WinGame();
}

void AKSGameModeBase::InitKeyFinishCount()
{
	if (KeyActor && GetWorld())
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), KeyActor, FoundActors);
		KeysFinish = FoundActors.Num();
	}
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Magenta, FString::Printf(TEXT("Initial Key Actors count: %d"), KeysFinish));
}

bool AKSGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if (PauseSet)
	{
		SetMatchState(EKSMatchState::Pause);
	}
	return PauseSet;
}

bool AKSGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(EKSMatchState::InProgress);
	}
	return PauseCleared;
}

void AKSGameModeBase::SetMatchState(EKSMatchState State)
{
	if (MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

void AKSGameModeBase::GetTimerUpdate()
{
	if (--GameCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GamerTimerHandle);
		GameOver();
	}
}

void AKSGameModeBase::GameOver()
{
	for (auto Pawn : TActorRange<ACharacter>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
			GetWorldTimerManager().ClearTimer(GamerTimerHandle);
		}
	}

	SetMatchState(EKSMatchState::GameOver);
}

void AKSGameModeBase::WinGame()
{
	for (auto Pawn : TActorRange<ACharacter>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
			GetWorldTimerManager().ClearTimer(GamerTimerHandle);
		}
	}

	SetMatchState(EKSMatchState::WinGame);
}
