#include "BehaviorTree/CPatrolPath.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"

ACPatrolPath::ACPatrolPath()
{
	// 드래그 하던 중에 호출, 드래그하고 놨을때 호출되는지 체크
	bRunConstructionScriptOnDrag = false;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<USplineComponent>(this, &Spline, "Spline", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);

	Spline->SetRelativeLocation(FVector(0, 0, 30));
	Spline->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 120));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->TextRenderColor = FColor::Red;
	Text->bHiddenInGame = true;

}

void ACPatrolPath::BeginPlay()
{
	Super::BeginPlay();

}

void ACPatrolPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

#if WITH_DDITOR
	// 에디터에 있는 함수이므로, WITH_DDITOR 붙여서 사용해야한다.
	Text->Text = FText::FromString(GetActorLabel());
#endif

	Spline->SetClosedLoop(bLoop);

}

FVector ACPatrolPath::GetMoveTo()
{
	// Index를 받아서 return
	return Spline->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);

}

void ACPatrolPath::UpdateIndex()
{
	int32 count = Spline->GetNumberOfSplinePoints();

	if (bReverse) // 역방향
	{
		if (Index > 0)
		{
			Index--;

			return;
		}

		if (Spline->IsClosedLoop()) // 정해진 구역을 루프로 사용할 것인지
		{
			Index = count - 1;

			return;
		}

		// 아니라면 1로 만들어주고, bReverse 뒤집어준다.
		Index = 1;
		bReverse = false;

		return;
	}

	// 정방향
	if (Index < count - 1)
	{
		Index++;

		return;
	}

	if (Spline->IsClosedLoop())
	{
		Index = 0;

		return;
	}

	// 전부 아니라면 -2. 역방향으로 돌려주기
	Index = count - 2;
	bReverse = true;

}