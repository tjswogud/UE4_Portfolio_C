#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_StraightCutting.generated.h"

UCLASS()
class MYPROJECT_06_API UCBTTaskNode_StraightCutting : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* StraightCutting_Montage;

public:
	UCBTTaskNode_StraightCutting();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	FTimerHandle TimerHandle;

};
