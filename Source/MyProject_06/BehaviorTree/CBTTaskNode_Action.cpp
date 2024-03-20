#include "BehaviorTree/CBTTaskNode_Action.h"
#include "Global.h"
#include "Character/CEnemy_AI.h"
#include "Character/CAIController.h"
#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"
#include "Weapons/CDoAction.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	NodeName = "Action";

	bNotifyTick = true;
	
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed);

	// 공격시 제자리에 멈춰서 액션을 취하도록,
	controller->StopMovement();
	weapon->DoAction();

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	bool bCheck = true;
	bCheck &= (state->IsIdleMode()); // &= 둘다 참이라는 의미
	bCheck &= (weapon->GetDoAction()->GetInAction() == false);

	// bCheck가 true 액션이 false라면 조건에 성립
	if (bCheck)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}

}

EBTNodeResult::Type UCBTTaskNode_Action::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	if (weapon == nullptr) // weapon이 없다면
		return EBTNodeResult::Failed; // 이 조건은 실패조건이므로, Failed

	bool bBeginAction = weapon->GetDoAction()->GetBeginAction();
	if (bBeginAction == false) // 액션에 들어온게 아니라면,
		weapon->GetDoAction()->Begin_DoAction(); // 액션 실행

	weapon->GetDoAction()->End_DoAction(); // End로 마무리

	return EBTNodeResult::Succeeded; // Hit된 후 일정시간이 지난후 공격할수 있도록 해주기 위해 Succeeded
}