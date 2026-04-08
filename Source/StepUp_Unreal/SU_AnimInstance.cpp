/*****************************************************************//**
 * \file   SU_AnimInstance.cpp
 * \brief  
 * 
 * \author Hyoje
 * \date   2026-4-8 
 *********************************************************************/


#include "SU_AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void USU_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);  
	ASU_Player* Player = Cast<ASU_Player>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		Speed = Player->GetCharacterMovement()->Velocity.Size2D();
		Direction = UKismetAnimationLibrary::CalculateDirection(Player->GetCharacterMovement()->Velocity, Player->GetActorRotation());
		CurrentWeapon = Player->CurrentWeapon;

		AimYaw = Player->GetBaseAimRotation().Yaw;
		//여기가 예상 문제인데.. +  카메라가 Orient를 하면 해결이 되는 문제 였나?
		AimPitch = Player->GetBaseAimRotation().Pitch * 0.01f;
	}
}
