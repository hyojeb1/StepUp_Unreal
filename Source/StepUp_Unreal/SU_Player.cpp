/*****************************************************************//**
 * \file   SU_Player.cpp
 * \brief  
 * 
 * \author Hyoje
 * \date   2026-3-31 
 * 
 * \brief  
 *		ABP_Unarmed는 CalculateDirection(Velocity, ActorRotation)으로 방향을 계산하는데, 
 *		이 방식은 캐릭터가 이동 방향을 바라보는 구조일 때 정상입니다. 
 *		그런데 BP_SU_Player는 템플릿과 다르게 bUseControllerRotationYaw = true, bOrientRotationToMovement = false라서 캐릭터가 이동 방향이 아니라 컨트롤러/카메라 방향을 바라보고 있었습니다. 
 *		그래서 같은 Velocity라도 Direction이 공용 Blend Space가 기대하는 값과 다르게 계산됐고, 
 *		왼쪽 입력이 좌측 스트레이프가 아니라 우측 후진 계열로 섞여 보인 겁니다.
 * 
 * \author Hyoje
 * \date   2026-4-2 
 *********************************************************************/
#include "SU_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"


ASU_Player::ASU_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Match the UE5 third-person template so CalculateDirection uses a compatible facing basis.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->bUseControllerDesiredRotation = false;
	CharacterMovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	CamBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamBoom"));
	CamBoom->SetupAttachment(RootComponent);
	CamBoom->bUsePawnControlRotation = true;

	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
	FollowCam->SetupAttachment(CamBoom);
	FollowCam->bUsePawnControlRotation = false;

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
