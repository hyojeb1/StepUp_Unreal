/*****************************************************************//**
 * \file   BasicAttributeSet.cpp
 * \brief  
 * 
 * \author Hyoje
 * \date   2026-4-3 
 *********************************************************************/


#include "BasicAttributeSet.h"
#include "Net/UnrealNetwork.h"

UBasicAttributeSet::UBasicAttributeSet()
{
	Health		= 100.0f;
	MaxHealth	= 100.0f;
	Stamina		= 100.0f;
	MaxStamina	= 100.0f;
}

void UBasicAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Health, COND_None, REPNOTIFY_Always);
}


