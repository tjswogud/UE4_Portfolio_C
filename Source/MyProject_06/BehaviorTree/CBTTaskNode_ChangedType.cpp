#include "BehaviorTree/CBTTaskNode_ChangedType.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/CBoss_AI.h"
#include "Character/CAIController.h"
#include "Character/CPlayer.h"
#include "Component/CAIBehaviorComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"

UCBTTaskNode_ChangedType::UCBTTaskNode_ChangedType()
{
	NodeName = "ChangedType";
	
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_ChangedType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACBoss_AI* boss = Cast<ACBoss_AI>(controller->GetPawn());
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(boss);
	AHumanType* target = Cast<ACPlayer>(aiState->GetTarget());

	if (!target)
		return EBTNodeResult::Failed;

	float targetDistance = target->GetDistanceTo(boss);

	if (!aiState->IsBossApproachMode())
	{
		aiState->SetBossApproachMode();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	}

	else
	{
		controller->GetBlackboardComponent()->SetValueAsEnum(aiState->AIStateBossType, FMath::RandRange(3, (uint8)EAIStateBossType::Max - 5));
		//aiState->SetBossAttackMode();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	}

	return EBTNodeResult::Succeeded;
}

void UCBTTaskNode_ChangedType::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}

EBTNodeResult::Type UCBTTaskNode_ChangedType::AbortTask(UBehaviorTreeComponent& Owner0Comp, uint8* NodeMemory)
{
	Super::AbortTask(Owner0Comp, NodeMemory);

	return EBTNodeResult::Succeeded;

}
