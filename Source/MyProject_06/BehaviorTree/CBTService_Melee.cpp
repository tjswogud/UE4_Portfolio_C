#include "BehaviorTree/CBTService_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Character/CAIController.h"
#include "Character/CEnemy_AI.h"
#include "Component/CStateComponent.h"
#include "Component/CAIBehaviorComponent.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Melee";

	Interval = 0.1f; // Tick 호출 간격
	RandomDeviation = 0.0f; // 

}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 실행에 주체는 ACAIController가 주축이 된다.
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	// Hitted 되었을때,
	if (state->IsHittedMode())
	{
		aiState->SetHittedMode();

		return;
	}

	ACharacter* target = aiState->GetTarget();
	if (target == nullptr)
	{
		// 타겟이 없으면, Patrol로 타겟을 찾게 된다
		aiState->SetPatrolMode();

		return;
	}

	//AActor* waitPoint = aiState->GetWaitPoint();
	//if (waitPoint)
	//{
	//	aiState->SetWaitPointMode();

	//	ai->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
	//		{
	//			// 딜레이 후 실행할 코드 작성
	//			aiState->SetPatrolMode();

	//		}, 5.0f, false);

	//	return;
	//}

	// 범위 안에 들어왓다면,
	float distance = ai->GetDistanceTo(target);
	if (distance < ActionRange)
	{
		// 공격 모드
		aiState->SetActionMode();

		return;
	}

	// 공격모드가 아니라면 추격 모드.
	aiState->SetApproachMode();
}