#include "BehaviorTree/CBTTaskNode_Boss_Attack.h"
#include "Global.h"
#include "Character/CBoss_AI.h"
#include "Character/CAIController.h"
#include "Character/CPlayer.h"
#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"
#include "Weapons/CDoAction.h"

UCBTTaskNode_Boss_Attack::UCBTTaskNode_Boss_Attack()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Boss_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACBoss_AI* ai = Cast<ACBoss_AI>(controller->GetPawn());
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);
	AHumanType* target = Cast<ACPlayer>(aiState->GetTarget());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed);

	controller->SetFocus(target);

	if (aiState->IsBossAttackMode())
	{
		ai->PlayAnimMontage(Attack_Montage, 1);

		ai->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
		{
			// 딜레이 후 실행할 코드 작성
			//aiState->SetBossApproachMode();
			aiState->SetBossChangedTypeMode();

		}, 3.0f, false);
	}

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Boss_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UCBTTaskNode_Boss_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	//ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	//ACBoss_AI* boss = Cast<ACBoss_AI>(controller->GetPawn());
	//UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(boss);

	//aiState->SetBossApproachMode();

	//ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	//ACBoss_AI* ai = Cast<ACBoss_AI>(controller->GetPawn());
	//UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);
	//AHumanType* target = Cast<ACPlayer>(aiState->GetTarget());

	//ai->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
	//	{
	//		
	//		aiState->SetBossApproachMode();

	//	}, 3.0f, false);

	//return EBTNodeResult::Succeeded;

	return Super::AbortTask(OwnerComp, NodeMemory);

}
