/*****************************************************************//**
 * \file   SU_PlayerController.cpp
 * \brief  
 * 
 * \author Hyoje
 * \date   2026-3-31 
 *********************************************************************/

#include "SU_PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ASU_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("ASU_PlayerController BeginPlay"));

	if (IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("IsLocalPlayerController true"));

		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			UE_LOG(LogTemp, Warning, TEXT("LocalPlayer valid"));

			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				UE_LOG(LogTemp, Warning, TEXT("InputSubsystem valid"));

				if (IMC_SU_Default)
				{
					UE_LOG(LogTemp, Warning, TEXT("IMC_SU_Default valid, adding mapping"));
					InputSystem->AddMappingContext(IMC_SU_Default, 0);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("IMC_SU_Default is null"));
				}
			}
		}
	}
}
