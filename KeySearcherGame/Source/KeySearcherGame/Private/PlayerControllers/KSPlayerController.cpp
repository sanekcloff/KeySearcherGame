// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/KSPlayerController.h"
#include "KSGameModeBase.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AKSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto Gamemode = Cast<AKSGameModeBase>(GetWorld()->GetAuthGameMode());
        if (Gamemode)
        {
            Gamemode->OnMatchStateChanged.AddUObject(this,&AKSPlayerController::OnMatchStateChanged);
        }
    }
}

void AKSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->ClearAllMappings();
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }
    if (!InputMappingContext || !PauseAction) return;

    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        Input->BindAction(PauseAction, ETriggerEvent::Started, this, &AKSPlayerController::OnPauseGame);
    }
}

void AKSPlayerController::OnMatchStateChanged(EKSMatchState State)
{
    if (State == EKSMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}
void AKSPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}