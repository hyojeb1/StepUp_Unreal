// Fill out your copyright notice in the Description page of Project Settings.


#include "SU_ZombieAnimInstance.h"
#include "SU_Zombie.h"
#include "GameFramework/CharacterMovementComponent.h"

void USU_ZombieAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ASU_Zombie* Zombie = Cast<ASU_Zombie>(TryGetPawnOwner());
	if (Zombie)
	{
		Speed = Zombie->GetCharacterMovement()->Velocity.Size2D();
		CurrentState = Zombie->CurrentState;
	}
}
