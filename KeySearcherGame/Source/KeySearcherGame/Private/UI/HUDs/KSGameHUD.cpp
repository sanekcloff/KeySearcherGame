// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDs/KSGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Gamemodes/KSGameModeBase.h"

void AKSGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AKSGameHUD::BeginPlay()
{
	GameWidgets.Add(EKSMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidgetClass));
	GameWidgets.Add(EKSMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EKSMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));
	GameWidgets.Add(EKSMatchState::WinGame, CreateWidget<UUserWidget>(GetWorld(), WinGameWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto Gamemode = Cast<AKSGameModeBase>(GetWorld()->GetAuthGameMode());
        if (Gamemode)
        {
            Gamemode->OnMatchStateChanged.AddUObject(this, &AKSGameHUD::OnMatchStateChanged);
        }
    }
}
void AKSGameHUD::OnMatchStateChanged(EKSMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State)));
}
