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
	////GPT 왈~~
	//const FVector Velocity = Player->GetVelocity();
	//const FVector HorizontalVelocity = FVector(Velocity.X, Velocity.Y, 0);
	//Speed = HorizontalVelocity.Size();
	//Direction = UKismetAnimationLibrary::CalculateDirection(HorizontalVelocity, Player->GetActorRotation());

	CurrentWeapon = Player->CurrentWeapon;

	AimYaw = Player->GetBaseAimRotation().Yaw;
	//여기가 예상 문제인데.. +  카메라가 Orient를 하면 해결이 되는 문제 였나?
	AimPitch = Player->GetBaseAimRotation().Pitch * 0.01f;

	////GPT 왈~~
	//// Aim Offset
	//const FRotator BaseAimRotation = Player->GetBaseAimRotation();
	//const FRotator ActorRotation = Player->GetActorRotation();

	//// 월드 기준 AimRotation을 캐릭터 기준 로컬 회전차로 변환
	//const FRotator DeltaRotation =
	//	UKismetMathLibrary::NormalizedDeltaRotator(BaseAimRotation, ActorRotation);

	//AimYaw = DeltaRotation.Yaw;
	//AimPitch = DeltaRotation.Pitch;

	//// 필요하면 에셋 축 범위에 맞춰 clamp
	//AimYaw = FMath::Clamp(AimYaw, -90.0f, 90.0f);
	//AimPitch = FMath::Clamp(AimPitch, -90.0f, 90.0f);

}
