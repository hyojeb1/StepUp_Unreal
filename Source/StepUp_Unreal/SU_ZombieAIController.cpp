// Fill out your copyright notice in the Description page of Project Settings.


#include "SU_ZombieAIController.h"
#include "Perception/AIPerceptionComponent.h"

ASU_ZombieAIController::ASU_ZombieAIController()
{
    Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
}

void ASU_ZombieAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    UE_LOG(LogTemp, Warning, TEXT("ZombieAIController OnPossess: %s"), *GetNameSafe(InPawn));
    //UE_LOG(LogTemp, Warning, TEXT("RunBTAsset: %s"), *GetNameSafe(RunBTAsset));

    if (RunBTAsset)
    {
        const bool bRan = RunBehaviorTree(RunBTAsset);
        UE_LOG(LogTemp, Warning, TEXT("RunBehaviorTree result: %s"), bRan ? TEXT("true") : TEXT("false"));
    }
}

void ASU_ZombieAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
