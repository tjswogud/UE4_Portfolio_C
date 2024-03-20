#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAIBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EAIStateType : uint8
{
	Wait = 0, Approach, WaitPoint ,Action, Patrol, Hitted, Avoid, Dead, Max,
};

UENUM(BlueprintType)
enum class EAIStateBossType : uint8
{
	Wait = 0, Approach, ChangedType, Attack, Skill1, Skill2, Skill3, Skill4, Hitted, Dead, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIStateTypeChanged, EAIStateType, InPrevType, EAIStateType, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIStateTypeBossChanged, EAIStateBossType, InPrevType, EAIStateBossType, InNewType);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_06_API UCAIBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Key")
		FName AIStateTypeKey = "AIState";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName TargetKey = "Target";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName PatrolLocationKey = "Patrol_Location";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName AvoidLocationKey = "Avoid_Location";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName BossDistanceKey = "BossDistance";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName AIStateBossType = "BossState";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName WaitPointKey = "WaitPoint";

public:
	EAIStateType GetType();
	EAIStateBossType GetBossType();

public:
	bool IsWaitMode();
	bool IsApproachMode();
	bool IsWaitPointMode();
	bool IsActionMode();
	bool IsPatrolMode();
	bool IsHittedMode();
	bool IsAvoidMode();
	bool IsDeadMode();

	bool IsBossWaitMode();
	bool IsBossApproachMode();
	bool IsBossChangedTypeMode();
	bool IsBossAttackMode();
	bool IsBossSkill1Mode();
	bool IsBossSkill2Mode();
	bool IsBossSkill3Mode();
	bool IsBossSkill4Mode();
	bool IsBossHittedMode();
	bool IsBossDeadMode();

public:
	UCAIBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public:
	class ACharacter* GetTarget();

	class AActor* GetWaitPoint();

public:
	FVector GetPatrolLocation();
	void SetPatrolLocation(const FVector& InLocation);

public:
	FVector GetAvoidLocation();
	float GetBossDistance();

public:
	void SetWaitMode();
	void SetApproachMode();
	void SetWaitPointMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetAvoidMode();
	void SetDeadMode();

	void SetBossWaitMode();
	void SetBossApproachMode();
	void SetBossChangedTypeMode();
	void SetBossAttackMode();
	void SetBossSkill1Mode();
	void SetBossSkill2Mode();
	void SetBossSkill3Mode();
	void SetBossSkill4Mode();
	void SetBossHittedMode();
	void SetBossDeadMode();

private:
	void ChangeType(EAIStateType InType);
	void ChangeBossType(EAIStateBossType InType);

public:
	FAIStateTypeChanged OnAIStateTypeChanged;
	FAIStateTypeBossChanged OnAIStateBossTypeChanged;

private:
	class UBlackboardComponent* Blackboard;
};
