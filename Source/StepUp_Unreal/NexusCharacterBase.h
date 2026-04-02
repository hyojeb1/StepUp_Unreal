/*****************************************************************//**
 * \file   NexusCharacterBase.h
 * \brief  결국 이건 그거임. 베이스!!! 넥서스 게임의 적과 플레이어가 상속받을...
 * 
 * \author Hyoje
 * \date   2026-4-2 
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "NexusCharacterBase.generated.h"

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

	// 갖고 오기
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// 서버
	virtual void PossessedBy(AController* NewController) override;
	// 클라
	virtual void OnRep_PlayerState() override;

protected:
	// ASC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// 타입, 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent2;

};
