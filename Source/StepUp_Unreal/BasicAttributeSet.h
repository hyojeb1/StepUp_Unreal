/*****************************************************************//**
 * \file   BasicAttributeSet.h
 * \brief  폴더가 곧 필터다.  <- 호감
 * https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-directory-structure
 * 
 * \author Hyoje
 * \date   2026-4-3 
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BasicAttributeSet.generated.h"

/**
 * 
 */

UCLASS()
class STEPUP_UNREAL_API UBasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UBasicAttributeSet();

	// 반드시 UFUNCTION()이 붙어야 합니다.
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Health, OldHealth);
	}

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& MaxHealth_)	
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, MaxHealth, MaxHealth_);
	}
	
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, Stamina, OldStamina);
	}

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& MaxStamina_)
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributeSet, MaxStamina, MaxStamina_);
	}

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetHealthValue() const { return Health.GetCurrentValue(); }

	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetMaxHealthValue() const { return MaxHealth.GetCurrentValue(); }

	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetStaminaValue() const { return Stamina.GetCurrentValue(); }

	UFUNCTION(BlueprintPure, Category = "Attributes")
	float GetMaxStaminaValue() const { return MaxStamina.GetCurrentValue(); }

public:
	// ReplicatedUsing = OnRep_Helth 이 매크로 인자는 
	// 복제 될 때, OnRep_Helth()를 실행함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Stamina);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxStamina);
};
