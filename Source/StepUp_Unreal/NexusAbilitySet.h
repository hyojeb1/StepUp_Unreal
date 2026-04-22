/*****************************************************************//**
 * \file   NexusAbilitySet.h
 * \brief  
 * 
 * \author Hyoje
 * \date   2026-4-22 
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "NexusAbilitySet.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FNexusAbilitySetEntry
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	bool bPassive = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	bool bAutoActivate = false;

};


/**
 * 
 */
UCLASS(BlueprintType)
class STEPUP_UNREAL_API UNexusAbilitySet : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Set")
	TArray<FNexusAbilitySetEntry> Abilities;


};
