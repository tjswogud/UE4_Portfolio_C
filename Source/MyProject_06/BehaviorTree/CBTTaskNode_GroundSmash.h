#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_GroundSmash.generated.h"

UCLASS()
class MYPROJECT_06_API UCBTTaskNode_GroundSmash : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* GroundSmash_Montage;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* SubAction_Montage;

public:
	UCBTTaskNode_GroundSmash();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	FTimerHandle TimerHandle;
	FTimerHandle Sub_TimerHandle;

};
