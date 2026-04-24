#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "NexusAbilitySysBPLibrary.generated.h"

class UAbilitySystemComponent;
class UNexusGameplayAbilityBase;

/**
 * GAS 조회용 헬퍼 함수 모음
 */
UCLASS()
class STEPUP_UNREAL_API UNexusAbilitySysBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * SpecHandle로부터 프로젝트 공통 Ability 베이스를 반환
	 */
	UFUNCTION(BlueprintPure, Category = "Nexus|Ability")
	static UNexusGameplayAbilityBase* GetNexusAbilityFromSpecHandle(
		UAbilitySystemComponent* AbilitySystemComponent,
		FGameplayAbilitySpecHandle SpecHandle
	);

	/**
	 * AbilitySpec의 Dynamic Source Tags에서 Input.Ability.* 태그를 찾아 반환
	 */
	UFUNCTION(BlueprintPure, Category = "Nexus|Ability")
	static FGameplayTag GetInputTagFromSpecHandle(
		UAbilitySystemComponent* AbilitySystemComponent,
		FGameplayAbilitySpecHandle SpecHandle
	);

	/**
	 * SpecHandle로부터 AbilityTag를 직접 반환
	 */
	UFUNCTION(BlueprintPure, Category = "Nexus|Ability")
	static FGameplayTag GetAbilityTagFromSpecHandle(
		UAbilitySystemComponent* AbilitySystemComponent,
		FGameplayAbilitySpecHandle SpecHandle
	);

	/**
	 * SpecHandle로부터 CooldownTag를 직접 반환
	 */
	UFUNCTION(BlueprintPure, Category = "Nexus|Ability")
	static FGameplayTag GetCooldownTagFromSpecHandle(
		UAbilitySystemComponent* AbilitySystemComponent,
		FGameplayAbilitySpecHandle SpecHandle
	);
};