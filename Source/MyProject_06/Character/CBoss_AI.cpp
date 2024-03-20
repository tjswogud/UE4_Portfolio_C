#include "Character/CBoss_AI.h"
#include "CAnimInstance.h"
#include "Global.h"
#include "Component/CWeaponComponent.h"
#include "Component/CAIBehaviorComponent.h"
#include "Components/WidgetComponent.h"
#include "Component/CStatusComponent.h"

ACBoss_AI::ACBoss_AI()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UCAIBehaviorComponent>(this, &Behavior, "Behavior");

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Hero_MercenaryWarriorUE4_v2/Content/MercenaryWarrior/Meshes/SK_MercenaryWarrior_WithoutHelmet.SK_MercenaryWarrior_WithoutHelmet'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/ABP/ABP_Boss.ABP_Boss_C'");
	GetMesh()->SetAnimClass(animInstance);

}

void ACBoss_AI::BeginPlay()
{
	Super::BeginPlay();

	// lee 보스의 웨폰 타입이 변경되지 않음 2024.01.31
	Weapons->SetSwordMode();
}

void ACBoss_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBoss_AI::UpdateLabelRenderScale()
{

}

void ACBoss_AI::Hitted()
{
	Super::Hitted();
	CheckTrue(State->IsDeadMode());

	Behavior->SetHittedMode();
}

void ACBoss_AI::End_Hitted()
{
	Super::End_Hitted();

	Behavior->SetWaitMode();
}
