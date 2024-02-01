#include "BehaviorTree/CBTTaskNode_Speed.h"
#include "Global.h"
#include "Character/CEnemy_AI.h"
#include "Character/CAIController.h"

UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	AHumanType* ai = Cast<AHumanType>(controller->GetPawn());
	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(ai);

	movement->SetSpeed(Type);

	return EBTNodeResult::Succeeded;
}
