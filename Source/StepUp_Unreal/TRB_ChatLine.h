// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "TRB_ChatTrigger.generated.h"

USTRUCT(BlueprintType)
struct STEPUP_UNREAL_API FTRB_ChatTrigger : public FTableRowBase
{
	GENERATED_BODY()


    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag EventType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag SubjectType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag SubjectID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag TargetType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag TargetID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag ActionType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag AttackType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag MapGroup;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag CombatState;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag PartyState;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag CharacterState;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag ValueMainType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ValueMain = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag ValueSubType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ValueSub = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag Speaker;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Note;
};
