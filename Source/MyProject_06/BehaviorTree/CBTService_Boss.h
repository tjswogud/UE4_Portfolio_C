#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Component/CAIBehaviorComponent.h"
#include "CBTService_Boss.generated.h"

UCLASS()
class MYPROJECT_06_API UCBTService_Boss : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_Boss();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FName BossDistance;

};
