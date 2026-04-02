/*****************************************************************//**
 * \file   NexusCharacterBase.h
 * \brief  1강 : https://www.youtube.com/watch?v=1QgGyndH_u4
 * 
 * \author Hyoje
 * \date   2026-4-2 
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "NexusCharacterBase.generated.h"

/**
 * IAbilitySystemInterface가 없으면 GAS가 이 액터의 ASC를 표준적으로 찾기 어렵다..
 */
UCLASS()
class STEPUP_UNREAL_API ANexusCharacterBase : public ACharacter, public IAbilitySystemInterface
{

	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANexusCharacterBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * GetAbilitySystemComponent()는 ASC 접근 창구다.
	 */
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/**
	 * PossessedBy()는 서버 측 초기화 지점이다.
	 * 
	 * \param NewController
	 */
	virtual void PossessedBy(AController* NewController) override;

	/**
	 * OnRep_PlayerState()는 클라이언트 측 초기화 지점이다.
	 * 
	 */
	virtual void OnRep_PlayerState() override;

protected:
	// ASC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/**
	 * 왜 ASCReplicationMode를 변수로 두는가
	 * → 플레이어와 AI에서 복제 정책을 다르게 쓸 수 있게 하려는 것
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	EGameplayEffectReplicationMode ASCReplicationMode = EGameplayEffectReplicationMode::Mixed;

};
