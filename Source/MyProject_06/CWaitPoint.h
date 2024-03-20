#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWaitPoint.generated.h"

UCLASS()
class MYPROJECT_06_API ACWaitPoint : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float SpawnTime;

public:	
	ACWaitPoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
