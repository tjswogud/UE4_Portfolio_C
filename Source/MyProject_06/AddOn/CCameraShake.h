#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "CCameraShake.generated.h"

UCLASS()
class MYPROJECT_06_API UCCameraShake : public UCameraModifier
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetLocation(const FVector& InLocation) { Location = InLocation; }
	FORCEINLINE void SetRotation(const FRotator& InRotation) { Rotation = InRotation; }

protected:
	void ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV) override;

private:
	FVector Location;
	FRotator Rotation;
};
