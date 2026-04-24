// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "TRB_ChatLine.generated.h"

USTRUCT(BlueprintType)
struct STEPUP_UNREAL_API FTRB_ChatLine : public FTableRowBase
{
	GENERATED_BODY()



    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag Speaker;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Order = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText LineText;
};
