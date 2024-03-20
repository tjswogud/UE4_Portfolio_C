#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_SpiritCrescent.generated.h"

UCLASS()
class MYPROJECT_06_API UCBTTaskNode_SpiritCrescent : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* SpiritCrescent_Montage;
public:
	UCBTTaskNode_SpiritCrescent();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	FTimerHandle TimerHandle;

};
