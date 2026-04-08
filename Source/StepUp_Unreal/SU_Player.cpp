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
#include "SU_WeaponBase.h"
#include "Kismet/KismetSystemLibrary.h" //충돌

#define 라인트레이스

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

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void ASU_Player::BeginPlay()
{
	Super::BeginPlay();
	
	EquipItem(DefalutWeapon);
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
		EIC->BindAction(IA_SU_Fire, ETriggerEvent::Started, this, &ASU_Player::Fire);
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

void ASU_Player::EquipItem(TSubclassOf<ASU_ItemBase> WeaponTemplate)
{
	Weapon->SetChildActorClass(WeaponTemplate);
	ASU_WeaponBase* EquippedWeapon = Cast<ASU_WeaponBase>(Weapon->GetChildActor());
	if (EquippedWeapon)
	{
		//switch(EquippedWeapon->WeaponType)
		//{
		//	case EWeaponState::Pistol:
				EquippedWeapon->AttachToComponent(
					GetMesh(), 
					FAttachmentTransformRules::KeepRelativeTransform,
					EquippedWeapon->SocketName
				);
				UE_LOG(LogTemp, Warning, TEXT("%s이 AttachToComponent"), *WeaponTemplate->GetName());
				EquippedWeapon->SetOwner(this);
				UE_LOG(LogTemp, Warning, TEXT("%s이 SetOwner"), *WeaponTemplate->GetName());
				CurrentWeapon = EquippedWeapon->WeaponType;
				UE_LOG(LogTemp, Warning, TEXT("%s이 WeaponType"), *WeaponTemplate->GetName());
		//	break;

		//	default:
		//		// 일단 임시로...
		//		//EquippedWeapon->AttachToComponent(
		//		//	GetMesh(),
		//		//	FAttachmentTransformRules::KeepRelativeTransform,
		//		//	EquippedWeapon->SocketName
		//		//);
		//		//EquippedWeapon->SetOwner(this);
		//		//CurrentWeapon = EquippedWeapon->WeaponType;
		//		break;
		//}

		
	}
}
/**
 * 이번엔 잘 만들어야 해.
 * 왜? 이건 네트워크 붙여 해
 * 
 * 일단 라인트레이싱
 */
void ASU_Player::Fire()
{
	//UE_LOG(LogTemp, Error, TEXT("WhyNotFire!"));

#ifdef 라인트레이스
	 FVector StartTrace = FollowCam->GetComponentLocation();
	 FVector EndTrace = StartTrace + (FollowCam->GetForwardVector() * 10000.0f); // 임시 초기화
	 
	 APlayerController* PC = Cast<APlayerController>(GetController());

	 if (PC)
	 {
		 int32 ViewportX = 0, ViewportY = 0;
		 FVector WorldLocation, WorldDirection;

		 PC->GetViewportSize(ViewportX, ViewportY);
		 PC->DeprojectScreenPositionToWorld(ViewportX / 2, ViewportY / 2, WorldLocation, WorldDirection);

		 EndTrace = StartTrace + (WorldDirection * 10000.0f);

		 TArray<TEnumAsByte<EObjectTypeQuery> > Objects;
		 Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		 Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		 Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

		 TArray<AActor*> IgnoredActors;
		 IgnoredActors.Add(this);

		 FHitResult HitResult;

		 //bool bIsHit = UKismetMathLibrary::LineTraceSingleForObjects(
			// GetWorld(),
			// StartTrace,
			// EndTrace,
			// Objects,
			// true, 
			// IgnoredActors,
			// EDrawDebugTrace::ForDuration,
			// HitResult,
			// true,
			// FColor::Red,
			// FColor::Red,
			// 1.0f
		 //);
		 bool bIsHit = UKismetSystemLibrary::LineTraceSingleForObjects(
			 GetWorld(),
			 StartTrace,
			 EndTrace,
			 Objects,
			 true,
			 IgnoredActors,
			 EDrawDebugTrace::ForDuration,
			 HitResult,
			 true,
			 FLinearColor::Red,
			 FLinearColor::Red,
			 1.0f
		 );

		 if (bIsHit)
		 {

		 }
	 }

#else // 탄도

#endif // 라인트레이스


}

void ASU_Player::StartFire()
{
}

void ASU_Player::StopFire()
{
}


void ASU_Player::Jump()
{

	Super::Jump();
}

void ASU_Player::StopJumping()
{
	Super::StopJumping();
}
