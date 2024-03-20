#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CANS_TimeDilation.generated.h"

UCLASS()
class MYPROJECT_06_API UCANS_TimeDilation : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Start_Time;

	UPROPERTY(EditAnywhere)
		float End_Time;

public:
	UCANS_TimeDilation();

public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
