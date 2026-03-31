/*****************************************************************//**
 * \file   SU_Player.cpp
 * \brief  
 * 
 * \author Hyoje
 * \date   2026-3-31 
 *********************************************************************/
#include "SU_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"


ASU_Player::ASU_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CamBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamBoom"));
	CamBoom->SetupAttachment(RootComponent);

	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
	FollowCam->SetupAttachment(CamBoom);

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0,0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0,-90.0f,0)
	);
}

// Called when the game starts or when spawned
void ASU_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASU_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASU_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent valid"));

		EIC->BindAction(IA_SU_Move, ETriggerEvent::Triggered, this, &ASU_Player::Move);
		EIC->BindAction(IA_SU_Jump, ETriggerEvent::Started, this, &ASU_Player::Jump);
		EIC->BindAction(IA_SU_Jump, ETriggerEvent::Canceled, this, &ASU_Player::StopJumping);
		EIC->BindAction(IA_SU_Aim, ETriggerEvent::Triggered, this, &ASU_Player::Aim);
		EIC->BindAction(IA_SU_Zoom, ETriggerEvent::Triggered, this, &ASU_Player::Zoom);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent cast failed"));
	}
}

/**
 *  .
 * 
 * \param Value
 */
void ASU_Player::Move(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();

	FVector NewForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0));
	FVector NewRightVector = UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, GetControlRotation().Roll));

	AddMovementInput(NewForwardVector * Direction.Y);
	AddMovementInput(NewRightVector * Direction.X);
}

void ASU_Player::Aim(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();

	AddControllerPitchInput(Direction.Y);
	AddControllerYawInput(Direction.X);
}

void ASU_Player::Zoom(const FInputActionValue& Value)
{
	float Zoom = Value.Get<float>();

	CamBoom->TargetArmLength += (Zoom * 30.f);

	CamBoom->TargetArmLength  = UKismetMathLibrary::Clamp(CamBoom->TargetArmLength, 30.0f, 600.0f);
}


void ASU_Player::Jump()
{
	Super::Jump();
}

void ASU_Player::StopJumping()
{
	Super::StopJumping();
}