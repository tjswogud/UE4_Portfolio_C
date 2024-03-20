#include "Character/CBoss.h"
#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/CMontagesComponent.h"
#include "Component/CMovementComponent.h"
#include "Component/CStatusComponent.h"
#include "Components/WidgetComponent.h"
#include "Weapons/CWeaponStructures.h"

ACBoss::ACBoss()
{
	
}

void ACBoss::BeginPlay()
{
	Super::BeginPlay();

	Movement->OnWalk();

	Create_DynamicMaterial(this);
	Change_Color(this, OriginColor);

	State->OnStateTypeChanged.AddDynamic(this, &ACBoss::OnStateTypeChanged);
}

float ACBoss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	/*float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage.Power = damage;
	Damage.Character = Cast<AHumanType>(EventInstigator->GetPawn());
	Damage.Causer = DamageCauser;
	Damage.Event = (FActionDamageEvent*)&DamageEvent;

	State->SetHittedMode();

	return damage;*/

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

}
void ACBoss::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Hitted: Hitted(); break;
	case EStateType::Dead: Dead(); break;
	}
}

void ACBoss::Hitted()
{
	// Apply Damage
	{
		Status->Damage(Damage.Power);
		Damage.Power = 0;

	}

	//TODO: 데미지 처리
	//TODO: 사망 처리

	// Change Color
	{
		// 맞으면 색 변경
		Change_Color(this, FLinearColor::Red);

		// 데미지 저장
		FTimerDelegate timerDelegate;
		timerDelegate.BindUFunction(this, "RestoreColor");

		GetWorld()->GetTimerManager().SetTimer(RestoreColor_TimerHandle, timerDelegate, 0.2f, false);
	}

	if (!!Damage.Event && !!Damage.Event->HitData)
	{
		FHitData* data = Damage.Event->HitData;

		//data->PlayMontage(this);
		data->PlayHitStop(GetWorld());
		data->PlaySoundWave(this);
		data->PlayEffect(GetWorld(), GetActorLocation(), GetActorRotation());

		if (Status->IsDead() == false)
		{
			// 때린 객체 바라보게 만들기.
			FVector start = GetActorLocation();
			FVector target = Damage.Character->GetActorLocation();
			FVector direction = target - start;
			direction.Normalize();

			LaunchCharacter(-direction * data->Launch, false, false); // 밀리는 Launch값
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target)); // 바라보게 만들기

		}
	}

	if (Status->IsDead())
	{
		State->SetDeadMode();

		return;
	}

	Damage.Character = nullptr;
	Damage.Causer = nullptr;
	Damage.Event = nullptr;
}

void ACBoss::End_Hitted()
{
	Super::End_Hitted();
}

void ACBoss::RestoreColor()
{
	Change_Color(this, OriginColor);

	GetWorld()->GetTimerManager().ClearTimer(RestoreColor_TimerHandle);
}

void ACBoss::Dead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Montages->PlayDeadMode();
}

void ACBoss::End_Dead()
{
	Destroy();
}