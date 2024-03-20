#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Patrol.generated.h"

UCLASS()
class MYPROJECT_06_API UCBTTaskNode_Patrol : public UBTTaskNode
{
	GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, Category = "Patrol")
        bool bDebugMode; // 디버깅 모드 on, off 선택

    UPROPERTY(EditAnywhere, Category = "Patrol")
        float AcceptanceDistance = 10; // 일정 거리에 들어오면 도달했다고 간주,

    UPROPERTY(EditAnywhere, Category = "Random")
        float RandomRadius = 2000; // 순찰 경로 없을때 랜덤 반경 범위

public:
	UCBTTaskNode_Patrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
