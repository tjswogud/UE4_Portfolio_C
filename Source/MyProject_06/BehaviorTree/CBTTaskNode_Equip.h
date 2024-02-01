#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Component/CWeaponComponent.h"
#include "CBTTaskNode_Equip.generated.h"

UCLASS()
class MYPROJECT_06_API UCBTTaskNode_Equip : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Type")
		EWeaponType Type;

public:
	UCBTTaskNode_Equip();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// 무기를 장착하는건 Tick에서 하게된다.
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
