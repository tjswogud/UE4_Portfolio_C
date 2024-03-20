#include "BehaviorTree/CBTTaskNode_Equip.h"
#include "Global.h"
#include "Character/CEnemy_AI.h"
#include "Character/CAIController.h"
#include "Component/CStateComponent.h"
#include "Weapons/CEquipment.h"

UCBTTaskNode_Equip::UCBTTaskNode_Equip()
{
	NodeName = "Equip";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Equip::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed); // 무기가 없다면 실행 x

	// 현재 장착하고있는 무기와, 장착할 무기가 같다면 이미 성공이므로,
	if (Type == weapon->GetCurWeaponType())
		return EBTNodeResult::Succeeded;

	switch (Type)
	{
	case EWeaponType::Sword: weapon->SetSwordMode(); break;
	case EWeaponType::Bow: weapon->SetBowMode(); break;
	case EWeaponType::Warp: weapon->SetWarpMode(); break;
	}

	return EBTNodeResult::InProgress; // 조건이 성공했다면, 대기
}

void UCBTTaskNode_Equip::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	const bool* bEquipped = weapon->GetEquipment()->GetEquipped(); // 장착이 완료 되었는지,

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	if (state->IsIdleMode() && *bEquipped) // 무기 장착이 아닌 상태, 장착이 완료되었다면,
	{
		// 끝내기
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}
}

EBTNodeResult::Type UCBTTaskNode_Equip::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	if (weapon == nullptr)
		return EBTNodeResult::Failed;

	bool bBeginEquip = weapon->GetEquipment()->GetBeginEquip();
	if (bBeginEquip == false)
		weapon->GetEquipment()->Begin_Equip();

	weapon->GetEquipment()->End_Equip();

	return EBTNodeResult::Aborted;
}