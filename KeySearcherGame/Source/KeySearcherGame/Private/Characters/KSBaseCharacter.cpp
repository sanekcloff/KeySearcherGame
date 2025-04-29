// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/KSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AKSBaseCharacter::AKSBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SocketOffset = FVector(0.0f, 0.0f, 80.0f);
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void AKSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AKSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(PlayerInputComponent, TEXT("PlayerInputComponent is not exist!"));

	PlayerInputComponent->BindAxis("MoveForward", this,&AKSBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKSBaseCharacter::MoveRight);
}

void AKSBaseCharacter::MoveForward(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(),Amount);
}

void AKSBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(),Amount);
}