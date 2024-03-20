#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_Launch.generated.h"

UCLASS()
class MYPROJECT_06_API UCAnimNotify_Launch : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Rate_X;

	UPROPERTY(EditAnywhere)
		float Rate_Y;

	UPROPERTY(EditAnywhere)
		float Rate_Z;

	UPROPERTY(EditAnywhere)
		bool isUpLaunch;

public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
