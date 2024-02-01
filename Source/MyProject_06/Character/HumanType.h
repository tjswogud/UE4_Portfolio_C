#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "Components/WidgetComponent.h"
#include "Weapons/CWeaponStructures.h"
#include "GenericTeamAgentInterface.h"
#include "HumanType.generated.h"

enum class EMoveDirection
{
	Forward = 0, Behind, Left, Right
};

UENUM()
enum class EVariousActionState : uint8
{
	UnHitable = 0, UnStopable,  Max
};

UCLASS()
class MYPROJECT_06_API AHumanType
	: public ACharacter
	, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 2;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UCMovementComponent* Movement;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UCWeaponComponent* Weapons;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		UWidgetComponent* HealthBar;
public:
	UPROPERTY()
		bool IsBlocking = false;

	UPROPERTY()
		bool CanParry = false;

	UPROPERTY()
		EVariousActionState ActionState = EVariousActionState::Max;

public:
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

public:
	AHumanType();

protected:
	UFUNCTION()
		virtual void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCMontagesComponent* GetMontages() { return Montages; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCStateComponent* GetState() { return State; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCStatusComponent* GetStatus() { return Status; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCMovementComponent* GetMovement() { return Movement; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCWeaponComponent* GetWeapons() { return Weapons; }

protected:
	virtual void Tick(float DeltaSeconds) override;

protected:
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	void UseSkill(int InIndex);

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
		void HiddenHealthBar(bool IsHidden);
protected:
	virtual void Idle();
	virtual void Hitted();
	virtual void Dead();
	virtual void Dodge();
	virtual void Ground();
	virtual void Rise();
	virtual void Groggy();
	virtual void Execute();
	virtual void Parried();
	virtual void Equip();
	virtual void Jump();

public:
	virtual void End_Dodge();
	virtual void End_Hitted();
	virtual void End_Dead() { }
	virtual void End_Ground();
	virtual void End_Rise();
	virtual void End_Groggy();
	virtual void End_Execute();
	virtual void End_Parried();
	virtual void End_Jump();

protected:
	virtual void BeginPlay() override;

public:
	void Create_DynamicMaterial(class ACharacter* InCharacter);
	void Change_Color(class ACharacter* InCharacter, FLinearColor InColor);

protected:
	struct FDamageData
	{
		float Power;
		float GroggyRate;
		class AHumanType* Character;
		class AActor* Causer;

		struct FActionDamageEvent* Event;


	} Damage;

	FTimerHandle RestoreColor_TimerHandle;

protected:
	void SetEndState();

public:
	EMoveDirection Direction;
};
