// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "NexusUIDataTableRow.generated.h"

class UTexture2D;

/**
 * 
 */
USTRUCT(BlueprintType)
struct  STEPUP_UNREAL_API FNexusUIDataTableRow : public FTableRowBase
{
	GENERATED_BODY()


    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
    FGameplayTag AbilityTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
    TObjectPtr<UTexture2D> Icon = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
    FGameplayTag CooldownTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
    FGameplayTag InputTag;
};
