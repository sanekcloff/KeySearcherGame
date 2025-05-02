// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/KSGameModeBase.h"
#include "Characters/KSBaseCharacter.h"
#include "PlayerControllers/KSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AKSGameModeBase::AKSGameModeBase()
{
	DefaultPawnClass = AKSBaseCharacter::StaticClass();
	PlayerControllerClass = AKSPlayerController::StaticClass();
	
}

void AKSGameModeBase::StartPlay()
{
	Super::StartPlay();
	InitKeyFinishCount();
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
