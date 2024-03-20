#include "CWaitPoint.h"
#include "Global.h"
#include "Character/HumanType.h"

ACWaitPoint::ACWaitPoint()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACWaitPoint::BeginPlay()
{
	Super::BeginPlay();

	this->SetLifeSpan(SpawnTime);
}

void ACWaitPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

