#include "CShockWave.h"
#include "Global.h"
#include "Character/HumanType.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"

ACShockWave::ACShockWave()
{
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box");
	CHelpers::CreateComponent<UNiagaraComponent>(this, &Niagara, "Niagara", Box);

	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Box->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
}

void ACShockWave::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACShockWave::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACShockWave::OnComponentEndOverlap);

	SetLifeSpan(0.5);
}

void ACShockWave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACShockWave::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(GetOwner() == OtherActor);

	Owner = Cast<AHumanType>(GetOwner());
	AHumanType* HittedActor = Cast<AHumanType>(OtherActor);

	if (!!Owner && HittedActor)
	{
		FRotator lookatRoation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HittedActor->GetActorLocation());
		//FVector launch = lookatRoation.Vector() * Rate;

		HitData.SendDamage(Owner, this, HittedActor);
		//Owner->LaunchCharacter(launch, false, false);
	}
}

void ACShockWave::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(GetOwner() == OtherActor);

	Owner = Cast<AHumanType>(GetOwner());
	AHumanType* HittedActor = Cast<AHumanType>(OtherActor);

	if (!!Owner && HittedActor)
	{
		Hitted.Remove(HittedActor);
	}
}

