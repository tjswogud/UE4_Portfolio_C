#include "CAIBehaviorComponent.h"
#include "Component/CAIBehaviorComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/CBoss.h"
#include "Component/CStatusComponent.h"
#include "Widget/CUserWidget_Label.h"

UCAIBehaviorComponent::UCAIBehaviorComponent()
{
	
}

void UCAIBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

}

ACharacter* UCAIBehaviorComponent::GetTarget()
{
	return Cast<ACharacter>(Blackboard->GetValueAsObject(TargetKey));
}

FVector UCAIBehaviorComponent::GetPatrolLocation()
{
	return Blackboard->GetValueAsVector(PatrolLocationKey);
}

void UCAIBehaviorComponent::SetPatrolLocation(const FVector& InLocation)
{
	Blackboard->SetValueAsVector(PatrolLocationKey, InLocation);
}

FVector UCAIBehaviorComponent::GetAvoidLocation()
{
	return Blackboard->GetValueAsVector(AvoidLocationKey);
}

float UCAIBehaviorComponent::GetBossDistance()
{
	return Blackboard->GetValueAsFloat(BossDistanceKey);
}

EAIStateType UCAIBehaviorComponent::GetType()
{
	return (EAIStateType)Blackboard->GetValueAsEnum(AIStateTypeKey);
}

EAIStateBossType UCAIBehaviorComponent::GetBossType()
{
	return (EAIStateBossType)Blackboard->GetValueAsEnum(AIStateBossType);
}

bool UCAIBehaviorComponent::IsWaitMode()
{
	return GetType() == EAIStateType::Wait;
}

bool UCAIBehaviorComponent::IsApproachMode()
{
	return GetType() == EAIStateType::Approach;
}

bool UCAIBehaviorComponent::IsActionMode()
{
	return GetType() == EAIStateType::Action;
}

bool UCAIBehaviorComponent::IsPatrolMode()
{
	return GetType() == EAIStateType::Patrol;
}

bool UCAIBehaviorComponent::IsHittedMode()
{
	return GetType() == EAIStateType::Hitted;
}

bool UCAIBehaviorComponent::IsAvoidMode()
{
	return GetType() == EAIStateType::Avoid;
}

bool UCAIBehaviorComponent::IsDeadMode()
{
	return GetType() == EAIStateType::Dead;
}

bool UCAIBehaviorComponent::IsBossWaitMode()
{
	return GetBossType() == EAIStateBossType::Wait;
}

bool UCAIBehaviorComponent::IsBossChangedTypeMode()
{
	return GetBossType() == EAIStateBossType::ChangedType;
}

bool UCAIBehaviorComponent::IsBossApproachMode()
{
	return GetBossType() == EAIStateBossType::Approach;
}

bool UCAIBehaviorComponent::IsBossAttackMode()
{
	return GetBossType() == EAIStateBossType::Attack;
}

bool UCAIBehaviorComponent::IsBossSkill1Mode()
{
	return GetBossType() == EAIStateBossType::Skill1;
}

bool UCAIBehaviorComponent::IsBossSkill2Mode()
{
	return GetBossType() == EAIStateBossType::Skill2;
}

bool UCAIBehaviorComponent::IsBossSkill3Mode()
{
	return GetBossType() == EAIStateBossType::Skill3;
}

bool UCAIBehaviorComponent::IsBossSkill4Mode()
{
	return GetBossType() == EAIStateBossType::Skill4;
}

bool UCAIBehaviorComponent::IsBossHittedMode()
{
	return GetBossType() == EAIStateBossType::Hitted;
}

bool UCAIBehaviorComponent::IsBossDeadMode()
{
	return GetBossType() == EAIStateBossType::Dead;
}

void UCAIBehaviorComponent::SetWaitMode()
{
	ChangeType(EAIStateType::Wait);
}

void UCAIBehaviorComponent::SetApproachMode()
{
	ChangeType(EAIStateType::Approach);
}

void UCAIBehaviorComponent::SetActionMode()
{
	ChangeType(EAIStateType::Action);
}

void UCAIBehaviorComponent::SetPatrolMode()
{
	ChangeType(EAIStateType::Patrol);
}

void UCAIBehaviorComponent::SetHittedMode()
{
	ChangeType(EAIStateType::Hitted);
}

void UCAIBehaviorComponent::SetAvoidMode()
{
	ChangeType(EAIStateType::Avoid);
}

void UCAIBehaviorComponent::SetDeadMode()
{
	ChangeType(EAIStateType::Dead);
}

void UCAIBehaviorComponent::SetBossWaitMode()
{
	ChangeBossType(EAIStateBossType::Wait);
}

void UCAIBehaviorComponent::SetBossChangedTypeMode()
{
	ChangeBossType(EAIStateBossType::ChangedType);
}

void UCAIBehaviorComponent::SetBossApproachMode()
{
	ChangeBossType(EAIStateBossType::Approach);
}

void UCAIBehaviorComponent::SetBossAttackMode()
{
	ChangeBossType(EAIStateBossType::Attack);
}

void UCAIBehaviorComponent::SetBossSkill1Mode()
{
	ChangeBossType(EAIStateBossType::Skill1);
}

void UCAIBehaviorComponent::SetBossSkill2Mode()
{
	ChangeBossType(EAIStateBossType::Skill2);
}

void UCAIBehaviorComponent::SetBossSkill3Mode()
{
	ChangeBossType(EAIStateBossType::Skill3);
}

void UCAIBehaviorComponent::SetBossSkill4Mode()
{
	ChangeBossType(EAIStateBossType::Skill4);
}

void UCAIBehaviorComponent::SetBossHittedMode()
{
	ChangeBossType(EAIStateBossType::Hitted);
}

void UCAIBehaviorComponent::SetBossDeadMode()
{
	ChangeBossType(EAIStateBossType::Dead);
}

void UCAIBehaviorComponent::ChangeType(EAIStateType InType)
{
	EAIStateType prevType = GetType();

	Blackboard->SetValueAsEnum(AIStateTypeKey, (uint8)InType);

	if (OnAIStateTypeChanged.IsBound())
		OnAIStateTypeChanged.Broadcast(prevType, InType);
}

void UCAIBehaviorComponent::ChangeBossType(EAIStateBossType InType)
{
	EAIStateBossType prevType = GetBossType();

	Blackboard->SetValueAsEnum(AIStateBossType, (uint8)InType);

	if (OnAIStateBossTypeChanged.IsBound())
		OnAIStateBossTypeChanged.Broadcast(prevType, InType);
}
