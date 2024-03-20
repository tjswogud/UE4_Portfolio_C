#include "BehaviorTree/CBTTaskNode_Approach.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/CBoss_AI.h"
#include "Character/CAIController.h"
#include "Character/CPlayer.h"
#include "Component/CAIBehaviorComponent.h"

UCBTTaskNode_Approach::UCBTTaskNode_Approach()
{
	NodeName = "Approach";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Approach::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACBoss_AI* boss = Cast<ACBoss_AI>(controller->GetPawn());
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(boss);
	AHumanType* target = Cast<ACPlayer>(aiState->GetTarget());

	float targetDistance = boss->GetDistanceTo(target);

	aiState->SetBossApproachMode();

	return EBTNodeResult::Succeeded;
}

void UCBTTaskNode_Approach::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}

EBTNodeResult::Type UCBTTaskNode_Approach::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Succeeded;

}
