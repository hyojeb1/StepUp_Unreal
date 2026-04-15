/*****************************************************************//**
 * \file   SU_BTTask_BlackboardBase.h
 * \brief  이름을 잘못 지은 클래스. 
 *			UBTTask_SetCurrentState입니다.  
 * 
 * \author Hyoje
 * \date   2026-4-14 
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SU_Zombie.h"

#include "SU_BTTask_BlackboardBase.generated.h"

/**
 * 
 */
UCLASS()
class STEPUP_UNREAL_API USU_BTTask_BlackboardBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EZombieState CurrentState;
};
