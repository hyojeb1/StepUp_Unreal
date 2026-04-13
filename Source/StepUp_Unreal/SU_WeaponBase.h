// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SU_ItemBase.h"
#include "SU_Player.h"

#include "SU_WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class STEPUP_UNREAL_API ASU_WeaponBase : public ASU_ItemBase
{
	GENERATED_BODY()

public:
	ASU_WeaponBase();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FName SocketName = TEXT("hand_r_WeaponSocket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EWeaponState WeaponType;

	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UMaterialInterface> DecalTemplate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UParticleSystem> MuzzleFlashEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UParticleSystem> HitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<USoundBase> FireSound;

};
