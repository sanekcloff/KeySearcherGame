// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LearningCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class KEYSEARCHERGAME_API ALearningCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALearningCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Compoenents")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Compoenents")
	UStaticMeshComponent* SwordMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* AttackAnimation;

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void TurnAround(float value);

	int Damage;
	void StartAttack();

public:
	UFUNCTION(BlueprintCallable)
	void LineTrace();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Animation")
	bool bIsAttacking = false;
};
