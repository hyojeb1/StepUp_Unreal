// Fill out your copyright notice in the Description page of Project Settings.


#include "SU_BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SU_Zombie.h"

EBTNodeResult::Type USU_BTTask_BlackboardBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ASU_Zombie* Zombie = Cast<ASU_Zombie>(OwnerComp.GetAIOwner()->GetPawn());

	if (!Zombie)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)CurrentState);

	Zombie->CurrentState = CurrentState;

	return EBTNodeResult::Type();
}
