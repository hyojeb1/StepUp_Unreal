/*****************************************************************//**
 * \file   SU_Player.h
 * \brief  https://github.com/junios-study/L20250316_P38/blob/main/Source/L20250316_P38/TPS/TPSPlayer.h
 * 
 * \author .Hyoje
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

	// 추가 
	void Zoom(const FInputActionValue& Value);


protected:
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

};
