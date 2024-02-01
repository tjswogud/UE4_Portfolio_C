#include "BehaviorTree/CBTTaskNode_Hitted.h"
#include "Global.h"
#include "Character/CEnemy_AI.h"
#include "Character/CAIController.h"
#include "Component/CStateComponent.h"

UCBTTaskNode_Hitted::UCBTTaskNode_Hitted()
{
	bNotifyTick = true;

	NodeName = "Hitted";

}

EBTNodeResult::Type UCBTTaskNode_Hitted::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());

	controller->StopMovement(); // Hit시 움직임 off

	return EBTNodeResult::InProgress;

}

void UCBTTaskNode_Hitted::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	if (state->IsHittedMode() == false)
	{
		// hit가 아니라면 종료.
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}

}