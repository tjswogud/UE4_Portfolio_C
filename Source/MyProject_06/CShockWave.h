#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/CWeaponStructures.h"
#include "CShockWave.generated.h"

UCLASS()
class MYPROJECT_06_API ACShockWave : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FHitData HitData;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UNiagaraComponent* Niagara;

	UPROPERTY(EditDefaultsOnly)
		float Rate;

public:	
	ACShockWave();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	TArray<class AHumanType*> Hitted;

	AHumanType* Owner;

	class ACharacter* character;
};
