// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SU_ZombieAIController.generated.h"


class UBehaviorTree;
class UAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class STEPUP_UNREAL_API ASU_ZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	
	ASU_ZombieAIController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAIPerceptionComponent> Perception;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UBehaviorTree> RunBTAsset;

};
