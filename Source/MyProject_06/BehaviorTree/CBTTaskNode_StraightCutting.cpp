#include "BehaviorTree/CBTTaskNode_StraightCutting.h"
#include "Global.h"
#include "Character/CBoss_AI.h"
#include "Character/CAIController.h"
#include "Character/CPlayer.h"
#include "Component/CMovementComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"
#include "Weapons/CDoAction.h"

UCBTTaskNode_StraightCutting::UCBTTaskNode_StraightCutting()
{
	NodeName = "StraightCutting";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_StraightCutting::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACBoss_AI* ai = Cast<ACBoss_AI>(controller->GetPawn());
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed);

	FRotator rotation = ai->GetActorRotation();

	ai->SetActorRotation(rotation);

	if (aiState->IsBossSkill3Mode())
	{
		ai->PlayAnimMontage(StraightCutting_Montage, 1);

		ai->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
		{
			//aiState->SetBossApproachMode();
			aiState->SetBossChangedTypeMode();

		}, 3.0f, false);
	}

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_StraightCutting::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

}

EBTNodeResult::Type UCBTTaskNode_StraightCutting::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return Super::AbortTask(OwnerComp, NodeMemory);

}
