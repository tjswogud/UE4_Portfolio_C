#include "Notifies/CANS_TimeDilation.h"
#include "Global.h"
#include "GameFramework/Actor.h"
#include "Character/HumanType.h"

UCANS_TimeDilation::UCANS_TimeDilation()
{
}

FString UCANS_TimeDilation::GetNotifyName_Implementation() const
{
	return "TimeDilation";

}

void UCANS_TimeDilation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	AHumanType* character = Cast<AHumanType>(MeshComp->GetOwner());
	CheckNull(character);

	UGameplayStatics::SetGlobalTimeDilation(character->GetWorld(), Start_Time);
	
}

void UCANS_TimeDilation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	AHumanType* character = Cast<AHumanType>(MeshComp->GetOwner());
	CheckNull(character);

	UGameplayStatics::SetGlobalTimeDilation(character->GetWorld(), End_Time);

}
