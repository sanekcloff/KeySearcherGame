// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/KSGameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UKSGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UKSGameOverWidget::OnRestart);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UKSGameOverWidget::OnExit);
	}
}

void UKSGameOverWidget::OnRestart()
{
	UGameplayStatics::OpenLevel(this, FName("TestMap"));
}

void UKSGameOverWidget::OnExit()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}