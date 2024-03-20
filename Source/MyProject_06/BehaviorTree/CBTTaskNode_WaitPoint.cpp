#include "BehaviorTree/CBTTaskNode_WaitPoint.h"
#include "CWaitPoint.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/CEnemy_AI.h"
#include "Character/CAIController.h"
#include "Component/CAIBehaviorComponent.h"
#include "Component/CMovementComponent.h"
#include "Component/CStateComponent.h"

UCBTTaskNode_WaitPoint::UCBTTaskNode_WaitPoint()
{
	NodeName = "WaitPoint";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_WaitPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	AHumanType* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);
	AActor* point = Cast<ACWaitPoint>(aiState->GetWaitPoint());

	//if (!point)
	//	return  EBTNodeResult::Failed;

	/*if (Point.Num() > 0)
	{
		int32 randomIndex = FMath::RandRange(0, Point.Num() - 1);
		TSubclassOf<AActor> TargetPoint = Point[randomIndex];

		AActor* PointLocation = UGameplayStatics::GetActorOfClass(this, TargetPoint);

		if (PointLocation)
		{
			ai->SetActorLocation(PointLocation->GetActorLocation());
		}
	}*/

	//if (Point.Num() > 0)
	//{
	//	FLatentActionInfo latentAction;
	//	latentAction.CallbackTarget = this;

	//	int32 randomIndex = FMath::RandRange(0, Point.Num() - 1);
	//	FVector location = FVector(randomIndex);

	//	UKismetSystemLibrary::MoveComponentTo(ai->GetCapsuleComponent(), location,
	//		ai->GetActorRotation(), false, false, 0.7f, false, EMoveComponentAction::Type::Move, latentAction);
	//}

	if (Point.Num() > 0)
	{
		Point.Add(TSoftObjectPtr<AActor>());

		int32 randomIndex = FMath::RandRange(0, Point.Num() - 1);
		TSoftObjectPtr<AActor> randomPoint = Point[randomIndex];

		controller->MoveToActor(randomPoint.Get());

		ai->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
			{
				// 딜레이 후 실행할 코드 작성
				aiState->SetPatrolMode();

			}, 5.0f, false);
	}

	return EBTNodeResult::InProgress;

}

void UCBTTaskNode_WaitPoint::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

EBTNodeResult::Type UCBTTaskNode_WaitPoint::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return Super::AbortTask(OwnerComp, NodeMemory);

}
