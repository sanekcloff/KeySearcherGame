// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/KSPlayerHudWidget.h"
#include "Gamemodes/KSGameModeBase.h"

int32 UKSPlayerHudWidget::GetGameSecondsRemaining() const
{
	const auto Gamemode = Cast<AKSGameModeBase>(GetWorld()->GetAuthGameMode());

	return Gamemode ? Gamemode->GetGameSecondsRemaining() : 0;
}
