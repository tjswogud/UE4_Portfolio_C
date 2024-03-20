#include "BehaviorTree/CBTTaskNode_UpperAttack.h"
#include "Global.h"
#include "Character/CBoss_AI.h"
#include "Character/CAIController.h"
#include "Character/CPlayer.h"
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
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed);

	ai->PlayAnimMontage(UpperAttack_Montage, 1);

	if (aiState->IsBossSkill1Mode())
	{
		ai->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
		{
			//aiState->SetBossApproachMode();
			aiState->SetBossChangedTypeMode();

		}, 3.0f, false);
	}

	return EBTNodeResult::InProgress;

}

void UCBTTaskNode_UpperAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}

EBTNodeResult::Type UCBTTaskNode_UpperAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	/*ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACBoss_AI* boss = Cast<ACBoss_AI>(controller->GetPawn());
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(boss);

	aiState->SetBossApproachMode();*/

	//ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	//ACBoss_AI* ai = Cast<ACBoss_AI>(controller->GetPawn());
	//UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);
	//AHumanType* target = Cast<ACPlayer>(aiState->GetTarget());
	//UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);

	//ai->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
	//	{
	//		
	//		aiState->SetBossApproachMode();

	//	}, 3.0f, false);

	//return EBTNodeResult::Succeeded;

	return Super::AbortTask(OwnerComp, NodeMemory);

}
