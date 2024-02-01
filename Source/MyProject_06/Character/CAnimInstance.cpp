#include "Character/CAnimInstance.h"
//#include "CEnemy_Range.h"
#include "Global.h"
#include "HumanType.h"
#include "Character/CPlayer.h"
#include "Component/CFeetComponent.h"
#include "Component/CStatusComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/CSubAction.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<AHumanType>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	if (!!Weapon)
		Weapon->OnWeaponTypeChange.AddDynamic(this, &UCAnimInstance::OnWeaponTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();

	FRotator rotator = OwnerCharacter->GetVelocity().ToOrientationRotator();
	FRotator rotator2 = OwnerCharacter->GetControlRotation();
	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(rotator, rotator2);
	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, delta, DeltaSeconds, 25);
	Direction = PrevRotation.Yaw;

	//if(Cast<ACEnemy_Range>(OwnerCharacter))
	//{
	//	Pitch = Cast<ACEnemy_Range>(OwnerCharacter)->pitchRange;
	//}
	
	Pitch = UKismetMathLibrary::FInterpTo(Pitch, OwnerCharacter->GetBaseAimRotation().Pitch, DeltaSeconds, 25);
	bFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();

	IsBlocking = Cast<AHumanType>(OwnerCharacter)->IsBlocking;

	if(Cast<AHumanType>(OwnerCharacter)->GetStatus()->CheckGroggy() == true && IsGroggy == false)
	{
		IsGroggy = true;
		IsEndGroggy = false;
	}
	else if(Cast<AHumanType>(OwnerCharacter)->GetStatus()->CheckGroggy() == false && IsGroggy == true)
	{
		IsGroggy = false;
	}
	
	if(	IsGroggy == true &&	Cast<AHumanType>(OwnerCharacter)->GetStatus()->CurGroggy <= 0)
	{
		IsEndGroggy = true;
	}

	UCFeetComponent* feet = CHelpers::GetComponent<UCFeetComponent>(OwnerCharacter);

	bFeet = false;
	if (!!feet)
	{
		if (OwnerCharacter->GetState()->IsIdleMode())
		{
			bFeet = true;
		}
		else
			bFeet = false;
		
		FeetData = feet->GetData();
	}


	CheckNull(Weapon);
	if (Weapon->GetSubAction() == nullptr) return;
	if (!IsValid(Weapon->GetSubAction())) return;

	if(WeaponType == EWeaponType::Bow && Weapon->GetSubAction()->GetInAction() == true)
	{
		bBow_Aiming = true;
	}
	else if(WeaponType == EWeaponType::Bow && Weapon->GetSubAction()->GetInAction() == false)
	{
		bBow_Aiming = false;
	}
	//if (!!Weapon->GetSubAction())
	//{
	//	bBow_Aiming = true;
	//	bBow_Aiming &= WeaponType == EWeaponType::Bow;
	//	bBow_Aiming &= Weapon->GetSubAction()->GetInAction();
	//}


}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}