// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SU_TPS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class STEPUP_UNREAL_API ASU_TPS_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void DrawHUD() override;
};
