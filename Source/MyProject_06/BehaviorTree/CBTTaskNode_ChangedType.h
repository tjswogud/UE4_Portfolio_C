#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_ChangedType.generated.h"

UCLASS()
class MYPROJECT_06_API UCBTTaskNode_ChangedType : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_ChangedType();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& Owner0Comp, uint8* NodeMemory) override;

private:
	FName Target;

};
