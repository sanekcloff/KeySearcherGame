// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/KSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 180;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
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
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	if (!InputMappingContext || !JumpAction || !MoveAction || !LookAction) return;

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		Input->BindAction(RunAction, ETriggerEvent::Started, this, &AKSBaseCharacter::RunStart);
		Input->BindAction(RunAction, ETriggerEvent::Completed, this, &AKSBaseCharacter::RunStop);

		Input->BindAction(CrouchAction, ETriggerEvent::Started, this, &AKSBaseCharacter::CrouchStart);
		Input->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AKSBaseCharacter::CrouchStop);

		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKSBaseCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKSBaseCharacter::Look);
	}
}

void AKSBaseCharacter::StopMoving()
{
	Move(0);
}

void AKSBaseCharacter::Move(const FInputActionValue& Value)
{
	const auto MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);


		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AKSBaseCharacter::Look(const FInputActionValue& Value)
{
	const auto MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(MovementVector.X);
		AddControllerPitchInput(MovementVector.Y);
	}
}

void AKSBaseCharacter::RunStart()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
}
void AKSBaseCharacter::RunStop()
{
	GetCharacterMovement()->MaxWalkSpeed = 180;
}

void AKSBaseCharacter::CrouchStart()
{
	Crouch();
	//GEngine->AddOnScreenDebugMessage(1,4,FColor::Red,TEXT("CROUCH!"));
}

void AKSBaseCharacter::CrouchStop()
{
	UnCrouch();
	//GEngine->AddOnScreenDebugMessage(1, 4, FColor::Red, TEXT("UNCROUCH!"));
}
