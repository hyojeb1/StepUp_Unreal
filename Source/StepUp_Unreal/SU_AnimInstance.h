/*****************************************************************//**
 * \file   SU_AnimInstance.h
 * \brief  
 * 
 * \author Hyoje
 * \date   2026-4-8 
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "SU_Player.h"

#include "SU_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STEPUP_UNREAL_API USU_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
	void AnimNotify_SkeletonNotifyReload();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Speed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Direction = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EWeaponState CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AimYaw = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AimPitch = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	uint8 bIsFire : 1 = false;
};
