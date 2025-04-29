// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/KSGameModeBase.h"
#include "Characters/KSBaseCharacter.h"
#include "PlayerControllers/KSPlayerController.h"

AKSGameModeBase::AKSGameModeBase()
{
	DefaultPawnClass = AKSBaseCharacter::StaticClass();
	PlayerControllerClass = AKSPlayerController::StaticClass();
}
