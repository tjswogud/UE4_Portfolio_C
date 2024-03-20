#include "BehaviorTree/CBTTaskNode_GroundSmash.h"
#include "Global.h"
#include "Character/CBoss_AI.h"
#include "Character/CAIController.h"
#include "Character/CPlayer.h"
#include "Component/CMovementComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"
#include "Weapons/CDoAction.h"

UCBTTaskNode_GroundSmash::UCBTTaskNode_GroundSmash()
{
	NodeName = "GroundSmash";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_GroundSmash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACBoss_AI* ai = Cast<ACBoss_AI>(controller->GetPawn());
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);
	AHumanType* target = Cast<AHumanType>(aiState->GetTarget());

	FVector launchRate = ai->GetActorUpVector();

	if (aiState->IsBossSkill4Mode())
	{
		ai->PlayAnimMontage(GroundSmash_Montage, 0.8);

		ai->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
		{
			TArray<AActor*> ignores;
			FHitResult hitResult;

			FLatentActionInfo latentAction;
			latentAction.CallbackTarget = this;

			FVector start = ai->GetActorLocation() + ai->GetActorForwardVector();
			FVector end = start + (ai->GetActorForwardVector() * 2000 + (ai->GetActorUpVector() * -800));

			UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end,ETraceTypeQuery::TraceTypeQuery1, false, ignores, EDrawDebugTrace::None, hitResult, true, FLinearColor::Red, FLinearColor::Green, 10.0f);

			if (hitResult.bBlockingHit)
			{
				FVector location = hitResult.ImpactPoint;

				UKismetSystemLibrary::MoveComponentTo(ai->GetCapsuleComponent(), FVector(location.X, location.Y, location.Z + 25.0f),
					ai->GetActorRotation(), false, false, 0.7f, false, EMoveComponentAction::Type::Move, latentAction);

			}
			ai->PlayAnimMontage(SubAction_Montage, 1);

			ai->GetWorld()->GetTimerManager().SetTimer(Sub_TimerHandle, [=]()
			{
				//aiState->SetBossApproachMode();
				aiState->SetBossChangedTypeMode();

			}, 5.0f, false);

		}, 1.3f, false);
	}

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_GroundSmash::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

EBTNodeResult::Type UCBTTaskNode_GroundSmash::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return Super::AbortTask(OwnerComp, NodeMemory);
}
