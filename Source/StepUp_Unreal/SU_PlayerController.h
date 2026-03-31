/*****************************************************************//**
 * \file   SU_PlayerController.h
 * \brief  
 * 
 * \author Hyoje
 * \date   2026-3-31 
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SU_PlayerController.generated.h"


class UInputMappingContext;

UCLASS()
class STEPUP_UNREAL_API ASU_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext>  IMC_SU_Default;


};
