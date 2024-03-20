#include "CBlade.h"
#include "Global.h"
#include "Character/HumanType.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

ACBlade::ACBlade()
{
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box");
	CHelpers::CreateComponent<UNiagaraComponent>(this, &Niagara, "Niagara", Box);
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");

	Projectile->ProjectileGravityScale = 0;
	Projectile->Activate();

	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Box->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
}

void ACBlade::BeginPlay()
{
	Super::BeginPlay();

	character = Cast<ACharacter>(GetOwner());
	Projectile->Velocity = character->GetActorForwardVector() * Projectile->InitialSpeed;

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACBlade::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACBlade::OnComponentEndOverlap);

	SetLifeSpan(5);
}

void ACBlade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBlade::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(GetOwner() == OtherActor);

	Owner = Cast<AHumanType>(GetOwner());
	AHumanType* HittedActor = Cast<AHumanType>(OtherActor);
	
	if (!!Owner && HittedActor)
	{
		FRotator lookatRoation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HittedActor->GetActorLocation());
		FVector launch = lookatRoation.Vector() * Rate;

		HitData.SendDamage(Owner, this, HittedActor);
		//Owner->LaunchCharacter(launch, false, false);
	}

}

void ACBlade::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(GetOwner() == OtherActor);

	Owner = Cast<AHumanType>(GetOwner());
	AHumanType* HittedActor = Cast<AHumanType>(OtherActor);

	if (!!Owner && HittedActor)
	{
		Hitted.Remove(HittedActor);
	}
}

