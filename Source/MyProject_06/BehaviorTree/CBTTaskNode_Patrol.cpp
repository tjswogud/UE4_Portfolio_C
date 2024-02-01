#include "BehaviorTree/CBTTaskNode_Patrol.h"
#include "Global.h"
#include "CPatrolPath.h"
#include "Components/SplineComponent.h"
#include "Component/CAIBehaviorComponent.h"
#include "Character/CEnemy_AI.h"
#include "Character/CAIController.h"
#include "NavigationSystem.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";

	bNotifyTick = true; // Tick 반드시 켜줘야 실행된다.
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCAIBehaviorComponent* behavior = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	// PatrolPath가 있을때
	if (!!ai->GetPatrolPath())
	{
		FVector moveToPoint = ai->GetPatrolPath()->GetMoveTo();
		behavior->SetPatrolLocation(moveToPoint);

		if (bDebugMode)
			DrawDebugSphere(ai->GetWorld(), moveToPoint, 25, 25, FColor::Green, true, 5);

		return EBTNodeResult::InProgress;
	}

	FVector location = ai->GetActorLocation();

	// Task를 보유한 AI가 사용하고 있는 네비게이션 Mesh를 구하기
	UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(ai->GetWorld());
	CheckNullResult(navSystem, EBTNodeResult::Failed); // 존재하지 않는다면, Failed

	FNavLocation point(location); // 초기값을 현재 위치로 정해주기.
	while (true)
	{
		if (navSystem->GetRandomPointInNavigableRadius(location, RandomRadius, point))
			break;

	}

	behavior->SetPatrolLocation(point.Location);

	if (bDebugMode)
		DrawDebugSphere(ai->GetWorld(), point.Location, 25, 25, FColor::Green, true, 5);

	return EBTNodeResult::InProgress; // 대기
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCAIBehaviorComponent* behavior = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	FVector location = behavior->GetPatrolLocation();
	EPathFollowingRequestResult::Type result = controller->MoveToLocation(location, AcceptanceDistance, false);

	switch (result)
	{
	case EPathFollowingRequestResult::Failed: // 못가는 곳이면,
	{
		// FinishLatentTask로 종료 시키기
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	break;

	case EPathFollowingRequestResult::AlreadyAtGoal: // 도달 했다면,
	{
		if (ai->GetPatrolPath()) // 순찰중이라면,
			ai->GetPatrolPath()->UpdateIndex(); // 순찰 다음 위치 구해주기.

		// 위에 조건이 아니라면 끝내고, 위에 다시 올라가서 조건 찾기
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	break;
	}

}