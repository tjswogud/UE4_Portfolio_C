#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_WaitPoint.generated.h"

UCLASS()
class MYPROJECT_06_API UCBTTaskNode_WaitPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<TSoftObjectPtr<AActor>> Point;

public:
	UCBTTaskNode_WaitPoint();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	FName WaitPoint;

	FTimerHandle TimerHandle;

};
