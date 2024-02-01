#include "BehaviorTree/CBTTaskNode_UpperAttack.h"
#include "Global.h"
#include "Character/CBoss_AI.h"
#include "Character/CAIController.h"
#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"
#include "Weapons/CDoAction.h"

UCBTTaskNode_UpperAttack::UCBTTaskNode_UpperAttack()
{
	NodeName = "UpperAttack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_UpperAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACBoss_AI* ai = Cast<ACBoss_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed);

	ai->PlayAnimMontage(UpperAttack_Montage, 1);

	return EBTNodeResult::InProgress;

}

void UCBTTaskNode_UpperAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}

EBTNodeResult::Type UCBTTaskNode_UpperAttack::AbortTask(UBehaviorTreeComponent& Owner0Comp, uint8* NodeMemory)
{
	Super::AbortTask(Owner0Comp, NodeMemory);

	return EBTNodeResult::Succeeded;

}
