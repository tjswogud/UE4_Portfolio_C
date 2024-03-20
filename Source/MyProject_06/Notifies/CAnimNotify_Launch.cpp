#include "Notifies/CAnimNotify_Launch.h"
#include "Global.h"
#include "Character/HumanType.h"

FString UCAnimNotify_Launch::GetNotifyName_Implementation() const
{
	return "Launch";
}

void UCAnimNotify_Launch::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	AHumanType* character = Cast<AHumanType>(MeshComp->GetOwner());
	CheckNull(character);

	FVector launchRate = character->GetActorForwardVector();
	FVector location = FVector(launchRate.X * Rate_X, launchRate.Y * Rate_Y, launchRate.Z * Rate_Z);

	character->LaunchCharacter(location, false, false);

	if (isUpLaunch)
	{
		FVector uplaunchRate = character->GetActorUpVector();
		character->LaunchCharacter(FVector(uplaunchRate.Z * Rate_Z), false, false);
	}
}
