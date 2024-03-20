#include "Notifies/CAN_SpawnActor.h"
#include "Global.h"
#include "Character/HumanType.h"

FString UCAN_SpawnActor::GetNotifyName_Implementation() const
{
	return "SpawnActor";
}

void UCAN_SpawnActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//CHelpers::GetComponent<AActor>(ActorClass);
	//ActorClass = ActorClass->StaticClass();
	//CheckNull(ActorClass);

	AHumanType* character = Cast<AHumanType>(MeshComp->GetOwner());
	CheckNull(character);

	FActorSpawnParameters params;
	params.Owner = character;

	FVector location = character->GetActorLocation() + character->GetActorForwardVector() * Rate;
	FRotator rotation = FVector(character->GetActorForwardVector()).Rotation();
	FTransform transform = UKismetMathLibrary::MakeTransform(location, rotation, FVector(1, 1, 1));

	if (!IsControlRotation && ActorClass)
	{
		character->GetWorld()->SpawnActor<AActor>(ActorClass, transform, params);
		
	}

	else if (IsControlRotation && ActorClass)
	{
		FTransform skillSocket = character->GetMesh()->GetSocketTransform(SocketName, ERelativeTransformSpace::RTS_World);
		FVector socketLocation = skillSocket.GetLocation() + skillSocket.GetRotation().GetForwardVector() * Rate;

		skillSocket.SetLocation(socketLocation);

		character->GetWorld()->SpawnActor<AActor>(ActorClass, skillSocket, params);
	}
}
