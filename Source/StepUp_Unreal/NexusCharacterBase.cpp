/*****************************************************************//**
 * \file   NexusCharacterBase.cpp
 * \brief  1강 : https://www.youtube.com/watch?v=1QgGyndH_u4
 * 
 * \author Hyoje
 * \date   2026-4-2 
 *********************************************************************/

#include "NexusCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "BasicAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


/**
 * 생성자에서 하는 일은 두 덩어리입니다.
 * 
 * A. ASC 생성과 복제 설정
 *	CreateDefaultSubobject
 *	SetIsReplicated(true)
 *	SetReplicationMode(...)
 * B. 캐릭터 기본 세팅
 *	캡슐 크기
 *	컨트롤러 회전 비활성화
 *	이동 방향 회전
 *	매쉬 정상화
 *  캠
 *	붐
 * 
 * 여기서 중요한 건 GAS 핵심은 A 덩어리라는 점입니다.
 * B는 부가 설정입니다.
 * 
 */
ANexusCharacterBase::ANexusCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//---A---
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true); // 네트워크 동기화됨
	AbilitySystemComponent->SetReplicationMode(ASCReplicationMode);

	//---B---
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->bOrientRotationToMovement = true;
	//CharacterMovementComponent->bUseControllerDesiredRotation = false;
	CharacterMovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0, -90.0f, 0)
	);

	// Add the BasicAttributeSet 
	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributeSet"));
}

// Called when the game starts or when spawned
void ANexusCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANexusCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANexusCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// ASC getter
UAbilitySystemComponent* ANexusCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

/**
 * 서버에서 캐릭터가 possession되는 시점에 ASC ActorInfo를 초기화한다.
 * 여기서는 Owner = this, Avatar = this다.
 * 즉, 이 Character가 ASC의 논리적 소유자이면서,
 * Ability가 실제로 적용되고 애니메이션/몽타주 등이 실행되는 현재 Avatar이기도 하다.
 * 
 * \param NewController
 */
void ANexusCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

/**
 * 클라에서도 서버와 마찬가지로 진행한다.
 */
void ANexusCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ANexusCharacterBase::GrantStartupAbilities()
{

}

