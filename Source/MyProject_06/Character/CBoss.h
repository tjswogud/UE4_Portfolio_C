#pragma once

#include "CoreMinimal.h"
#include "CPlayer.h"
#include "GameFramework/Character.h"
#include "Character/HumanType.h"
#include "Component/CAIBehaviorComponent.h"
#include "CBoss.generated.h"

UCLASS()
class MYPROJECT_06_API ACBoss : public AHumanType
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Color")
		FLinearColor OriginColor = FLinearColor::White;

public:
	UPROPERTY(BlueprintReadWrite)
		EAIStateBossType AIBossState = EAIStateBossType::Max;

public:
	ACBoss();

protected:
	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	virtual void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType) override;

protected:
	virtual void Hitted() override;

public:
	virtual void End_Hitted() override;

private:
	UFUNCTION()
		void RestoreColor();

protected:
	virtual void Dead() override;

public:
	virtual void End_Dead() override;

private:
	FTimerHandle RestoreColor_TimerHandle;
};
