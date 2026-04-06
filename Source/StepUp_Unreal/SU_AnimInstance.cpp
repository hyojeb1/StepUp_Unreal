// Fill out your copyright notice in the Description page of Project Settings.


#include "SU_AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void USU_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Pawn에 있는 정보를 복사해온다.(Pawn 네트워크로 정보 주고 받음)
	ASU_Player* Player = Cast<ASU_Player>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		Speed = Player->GetCharacterMovement()->Velocity.Size2D();
		Direction = UKismetAnimationLibrary::CalculateDirection(Player->GetCharacterMovement()->Velocity, Player->GetActorRotation());
		CurrentWeapon = Player->CurrentWeapon;

		AimYaw = Player->GetBaseAimRotation().Yaw;
		AimPitch = Player->GetBaseAimRotation().Pitch;
	}
}
