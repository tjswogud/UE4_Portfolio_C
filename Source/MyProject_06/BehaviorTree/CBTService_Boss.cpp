#include "BehaviorTree/CBTService_Boss.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Character/CAIController.h"
#include "Character/CBoss.h"
#include "Character/CBoss_AI.h"
#include "Character/CPlayer.h"
#include "Component/CStateComponent.h"
#include "Component/CAIBehaviorComponent.h"

UCBTService_Boss::UCBTService_Boss()
{
	NodeName = "Boss";
	
	Interval = 0.1f;
	RandomDeviation = 0.0f;

}

void UCBTService_Boss::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	AHumanType* boss = Cast<ACBoss_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(boss);
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(boss);
	AHumanType* target = Cast<ACPlayer>(aiState->GetTarget());

	if (!target)
		return;

	float targetDistance = boss->GetDistanceTo(target);

	BossDistance = aiState->BossDistanceKey;

	controller->GetBlackboardComponent()->SetValueAsFloat(BossDistance, targetDistance);

	//CLog::Print(target);
	CLog::Print(targetDistance);
	//CLog::Print(BossDistance);

}
