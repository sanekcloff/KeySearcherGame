// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/KSWinGameWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UKSWinGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UKSWinGameWidget::OnRestart);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UKSWinGameWidget::OnExit);
	}
}

void UKSWinGameWidget::OnRestart()
{
	UGameplayStatics::OpenLevel(this, FName("TestMap"));
}

void UKSWinGameWidget::OnExit()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
