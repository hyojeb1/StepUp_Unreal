// Fill out your copyright notice in the Description page of Project Settings.


#include "SU_Zombie.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASU_Zombie::ASU_Zombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0, -90.0f, 0)
	);

}

// Called when the game starts or when spawned
void ASU_Zombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASU_Zombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASU_Zombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

