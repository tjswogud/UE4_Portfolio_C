#include "Notifies/CAN_LookAtTarget.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/HumanType.h"
#include "Character/CEnemy.h"
#include "Component/CMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

FString UCAN_LookAtTarget::GetNotifyName_Implementation() const
{
	return "LookAtTarget";
}

void UCAN_LookAtTarget::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	AHumanType* Owner = Cast<AHumanType>(MeshComp->GetOwner());
	CheckNull(Owner);


	/*if (Cast<ACEnemy_Melee>(Owner))
	{

		Target = Cast<AHumanType>(Cast<ACEnemy_AIController>(Owner->GetController())->GetBlackboardComponent()->GetValueAsObject(ACEnemy_AIController::Target));
	}
	else if (Cast<ACEnemy_Range>(Owner))
	{
		Target = Cast<AHumanType>(Cast<ACEnemy_AIController_Range>(Owner->GetController())->GetBlackboardComponent()->GetValueAsObject(ACEnemy_AIController_Range::Target));
	}
	else if (Cast<ACEnemy_Boss>(Owner))
	{
		Target = Cast<AHumanType>(Cast<ACEnemy_AIController_Boss>(Owner->GetController())->GetBlackboardComponent()->GetValueAsObject(ACEnemy_AIController_Boss::Target));
	}*/

	if (!IsValid(Target)) return;

	FRotator Rotator;
	if(bUsePitchAndRoll)
	{
		Rotator = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), Target->GetActorLocation());

	}
	else
	{
		
		Rotator = UKismetMathLibrary::FindLookAtRotation(CHelpers::GetVector2D(Owner->GetActorLocation()), CHelpers::GetVector2D(Target->GetActorLocation()));
	}




	Owner->SetActorRotation(Rotator);
}
