#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_SpawnActor.generated.h"

UCLASS()
class MYPROJECT_06_API UCAN_SpawnActor : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> ActorClass;

	UPROPERTY(EditAnywhere)
		bool IsControlRotation;

	UPROPERTY(EditAnywhere)
		float Rate;

	UPROPERTY(EditAnywhere)
		FName SocketName;
		
public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
