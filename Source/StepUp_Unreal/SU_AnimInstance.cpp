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
#include "Kismet/KismetMathLibrary.h"

void USU_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);  
	ASU_Player* Player = Cast<ASU_Player>(TryGetPawnOwner());

	if (!IsValid(Player))
	{
		return;
	}

	
	Speed = Player->GetCharacterMovement()->Velocity.Size2D();
	Direction = UKismetAnimationLibrary::CalculateDirection(Player->GetCharacterMovement()->Velocity, Player->GetActorRotation());

	CurrentWeapon = Player->CurrentWeapon;

	AimYaw = Player->GetBaseAimRotation().Yaw;
	AimPitch = Player->GetBaseAimRotation().Pitch;

	bIsFire = Player->bIsFire;

}

void USU_AnimInstance::AnimNotify_SkeletonNotifyReload()
{
	UE_LOG(LogTemp, Warning, TEXT("AnimNotify_SkeletonNotifyReload"));
}
