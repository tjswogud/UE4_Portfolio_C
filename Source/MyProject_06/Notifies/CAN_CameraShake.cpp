#include "Notifies/CAN_CameraShake.h"
#include "Global.h"
#include "Component/CWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapons/CDoAction.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraShake.h"

FString UCAN_CameraShake::GetNotifyName_Implementation() const
{
	return "CameraShake";
}

void UCAN_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(Character);

	APlayerController* controller = Character->GetController<APlayerController>();
	CheckNull(controller);

	if(IsValid(CameraShake))
	{
		//UGameplayStatics::GetPlayerController(Character->GetWorld(), 0)->ClientPlayCameraShake(CameraShake);
		controller->PlayerCameraManager->StartCameraShake(CameraShake);
	}
}
