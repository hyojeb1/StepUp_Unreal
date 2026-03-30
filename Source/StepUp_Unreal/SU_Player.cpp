/////////////////////////////////////////////////////////////////////
//! @file   SU_Player.cpp
//! @brief  
//!  
//! @author Hyoje
//! @date   2026-3-30 
/////////////////////////////////////////////////////////////////////
#include "SU_Player.h"

ASU_Player::ASU_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASU_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASU_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASU_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

