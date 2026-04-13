// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SU_Zombie.generated.h"

UENUM(BlueprintType)
enum class EZombieState : uint8
{
	Idle = 0 UMETA(DisplayName = "Idle"),
	Chase = 1 UMETA(DisplayName = "Chase"),
	Battle = 2 UMETA(DisplayName = "Battle"),
	Death = 3 UMETA(DisplayName = "Death")
};

UCLASS()
class STEPUP_UNREAL_API ASU_Zombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASU_Zombie();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EZombieState CurrentState;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	uint8 HP = 100;
};
