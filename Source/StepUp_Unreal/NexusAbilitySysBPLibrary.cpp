#include "NexusAbilitySysBPLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "NexusGameplayAbilityBase.h"

UNexusGameplayAbilityBase* UNexusAbilitySysBPLibrary::GetNexusAbilityFromSpecHandle(
	UAbilitySystemComponent* AbilitySystemComponent,
	FGameplayAbilitySpecHandle SpecHandle
)
{
	if (!AbilitySystemComponent || !SpecHandle.IsValid())
	{
		return nullptr;
	}

	FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle);
	if (!Spec || !Spec->Ability)
	{
		return nullptr;
	}

	return Cast<UNexusGameplayAbilityBase>(Spec->Ability);
}

FGameplayTag UNexusAbilitySysBPLibrary::GetInputTagFromSpecHandle(
	UAbilitySystemComponent* AbilitySystemComponent,
	FGameplayAbilitySpecHandle SpecHandle
)
{
	if (!AbilitySystemComponent || !SpecHandle.IsValid())
	{
		return FGameplayTag();
	}

	FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle);
	if (!Spec)
	{
		return FGameplayTag();
	}

	const FGameplayTagContainer& DynamicTags = Spec->GetDynamicSpecSourceTags();

	for (const FGameplayTag& Tag : DynamicTags)
	{
		if (Tag.IsValid() && Tag.ToString().StartsWith(TEXT("Input.Ability.")))
		{
			return Tag;
		}
	}

	return FGameplayTag();
}

FGameplayTag UNexusAbilitySysBPLibrary::GetAbilityTagFromSpecHandle(
	UAbilitySystemComponent* AbilitySystemComponent,
	FGameplayAbilitySpecHandle SpecHandle
)
{
	const UNexusGameplayAbilityBase* NexusAbility =
		GetNexusAbilityFromSpecHandle(AbilitySystemComponent, SpecHandle);

	if (!NexusAbility)
	{
		return FGameplayTag();
	}

	return NexusAbility->AbilityTag;
}

FGameplayTag UNexusAbilitySysBPLibrary::GetCooldownTagFromSpecHandle(
	UAbilitySystemComponent* AbilitySystemComponent,
	FGameplayAbilitySpecHandle SpecHandle
)
{
	const UNexusGameplayAbilityBase* NexusAbility =
		GetNexusAbilityFromSpecHandle(AbilitySystemComponent, SpecHandle);

	if (!NexusAbility)
	{
		return FGameplayTag();
	}

	return NexusAbility->CooldownTag;
}