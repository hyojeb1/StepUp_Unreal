/*****************************************************************//**
 * \file   SU_Player.h
 * \brief  https://github.com/junios-study/L20250316_P38/blob/main/Source/L20250316_P38/TPS/TPSPlayer.h
 * 
 * \author Hyoje
 * \date   2026-3-31 
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "SU_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class ASU_WeaponBase;

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Unarmed = 0 UMETA(Display = "Unarmed"),
	Pistol = 10 UMETA(Display = "Pistol"),
	Rifle = 20 UMETA(Display = "Rifle"),
	GrenadeLauncher = 30 UMETA(Display = "GrenadeLauncher"),
};

UCLASS()
class STEPUP_UNREAL_API ASU_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASU_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void Aim(const FInputActionValue& Value);

	void Jump();
	void StopJumping();

	void Zoom(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void EquipItem(TSubclassOf<ASU_ItemBase> item);

	void Fire();

	void StartFire();

	void StopFire();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> FollowCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> CamBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_SU_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_SU_Aim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_SU_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_SU_Zoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_SU_Fire;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EWeaponState CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<class ASU_WeaponBase> DefalutWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UChildActorComponent> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	uint8 bIsFiring : 1 = false;
};
