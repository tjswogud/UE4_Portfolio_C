#pragma once

#include "CoreMinimal.h"
#include "Character/CBoss.h"
#include "CBoss_AI.generated.h"

UCLASS()
class MYPROJECT_06_API ACBoss_AI : public ACBoss
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCAIBehaviorComponent* Behavior;

public:
	ACBoss_AI();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void UpdateLabelRenderScale();

protected:
	void Hitted() override;

public:
	void End_Hitted() override;

};
