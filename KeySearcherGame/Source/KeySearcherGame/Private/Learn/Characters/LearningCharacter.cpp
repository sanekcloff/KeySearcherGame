// Fill out your copyright notice in the Description page of Project Settings.


#include "Learn/Characters/LearningCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALearningCharacter::ALearningCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = true;

	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>("SwordComponent");
	SwordMesh->SetupAttachment(GetMesh(), FName("SwordSocket"));

}

// Called when the game starts or when spawned
void ALearningCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALearningCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALearningCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &ALearningCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALearningCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ALearningCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ALearningCharacter::TurnAround);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ALearningCharacter::StartAttack);

}

void ALearningCharacter::MoveForward(float value)
{
	if (value == 0) return;
	AddMovementInput(GetActorForwardVector(), value);
}
void ALearningCharacter::MoveRight(float value)
{
	if (value == 0) return;
	AddMovementInput(GetActorRightVector(), value);
}
void ALearningCharacter::LookUp(float value)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("UP/DOWN: %f"),value));
	AddControllerPitchInput(value);
}
void ALearningCharacter::TurnAround(float value)
{
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, FString::Printf(TEXT("RIGHT/LEFT: %f"), value));
	AddControllerYawInput(value);
}

void ALearningCharacter::StartAttack()
{
	if (!AttackAnimation || bIsAttacking) return;
	GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Red, FString::Printf(TEXT("Is attack: %s"), bIsAttacking ? TEXT("True") : TEXT("False")),true);

	GetMesh()->PlayAnimation(AttackAnimation, false);
	bIsAttacking = true;
}

void ALearningCharacter::LineTrace()
{
	if (!GetWorld()) return;
	FVector StartLocation = SwordMesh->GetSocketLocation(FName("Start"));
	FVector EndLocation = SwordMesh->GetSocketLocation(FName("End"));

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1, 0, 1);

	if (HitResult.bBlockingHit)
	{
		AActor* ActorHit = HitResult.GetActor();
		ActorHit->Destroy();
	}
}
