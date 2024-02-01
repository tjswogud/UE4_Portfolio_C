#include "Character/CAIController.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/CEnemy_AI.h"
#include "Component/CAIBehaviorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACAIController::ACAIController()
{
	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");

	// CreateDefaultSubobject은 동적할당 할때 사용, NewObject는 런타임때 사용
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 600; // 감지 거리
	Sight->LoseSightRadius = 800; // 잃는 거리
	Sight->PeripheralVisionAngleDegrees = 45; // 시야각
	Sight->SetMaxAge(2); // 수명시간

	Sight->DetectionByAffiliation.bDetectEnemies = true; // 적을 감지하겠다.
	Sight->DetectionByAffiliation.bDetectNeutrals = false; // 중립은 감지 x
	Sight->DetectionByAffiliation.bDetectFriendlies = false; // 아군도 현재는 감지x로 설정

	Perception->ConfigureSense(*Sight); // 감지객체 등록, 주소로 받는 이유는 여러개 사용할때 배열로 사용하면된다.
	// SetDominantSense은 우선순위 등록, Sense return 해주는 함수
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Enemy = Cast<AHumanType>(InPawn); // 캐스팅해서 인식시켜 놓는다.
	SetGenericTeamId(Enemy->GetTeamID()); // BP에서는 사용이 불가능한 아군, 적군 나누기 가능

	CheckNull(Enemy->GetBehaviorTree());
	// 블랙보드를 사용, 실제 사용할 블랙보드 지정
	UseBlackboard(Enemy->GetBehaviorTree()->BlackboardAsset, Blackboard);

	Behavior = CHelpers::GetComponent<UCAIBehaviorComponent>(Enemy); // Enemy에서 찾아오기
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(Enemy->GetBehaviorTree()); // 블랙보드 실행
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	if (actors.Num() > 0)
	{
		Blackboard->SetValueAsObject("Target", actors[0]);

		return;
	}

	Blackboard->SetValueAsObject("Target", nullptr);
}