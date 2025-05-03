// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/KSPauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Gameframework/GameModeBase.h"

void UKSPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UKSPauseWidget::OnRestart);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UKSPauseWidget::OnExit);
	}
	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this,&UKSPauseWidget::OnContinue);
	}
}

void UKSPauseWidget::OnContinue()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UKSPauseWidget::OnRestart()
{
	UGameplayStatics::OpenLevel(this, FName("TestMap"));
}

void UKSPauseWidget::OnExit()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

