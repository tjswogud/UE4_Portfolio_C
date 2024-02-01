#include "Character/CEnemy_AI.h"
#include "Global.h"
#include "Component/CWeaponComponent.h"
#include "Component/CAIBehaviorComponent.h"
#include "Components/WidgetComponent.h"
#include "Component/CStatusComponent.h"
#include "Widget/CUserWidget_Label.h"

ACEnemy_AI::ACEnemy_AI()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UWidgetComponent>(this, &LabelWidget, "Label", GetMesh());
	CHelpers::CreateActorComponent<UCAIBehaviorComponent>(this, &Behavior, "Behavior");

	TSubclassOf<UCUserWidget_Label> labelClass;
	CHelpers::GetClass<UCUserWidget_Label>(&labelClass, "WidgetBlueprint'/Game/Widgets/WB_Label.WB_Label_C'");
	LabelWidget->SetWidgetClass(labelClass);
	LabelWidget->SetRelativeLocation(FVector(0, 0, 220));
	LabelWidget->SetDrawSize(FVector2D(120, 0));
	LabelWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACEnemy_AI::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	LabelWidget->InitWidget();

	UCUserWidget_Label* label = Cast<UCUserWidget_Label>(LabelWidget->GetUserWidgetObject());
	label->UpdateHealth(Status->GetHealth(), Status->GetMaxHealth());
	label->UpdateName(GetName());
	label->UpdateControllerName(GetController()->GetName());
#endif
}

void ACEnemy_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCUserWidget_Label* label = Cast<UCUserWidget_Label>(LabelWidget->GetUserWidgetObject());

	if (!!label)
	{
		label->UpdateHealth(Status->GetHealth(), Status->GetMaxHealth());

		UpdateLabelRenderScale();
	}
}

void ACEnemy_AI::UpdateLabelRenderScale()
{
	UCUserWidget_Label* label = Cast<UCUserWidget_Label>(LabelWidget->GetUserWidgetObject());
	CheckNull(label);

	APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	FVector cameraLocation = cameraManager->GetCameraLocation();
	FVector targetLocation = GetController()->GetTargetLocation();

	float distance = FVector::Distance(cameraLocation, targetLocation);
	float sizeRate = 1.0f - (distance / LabelViewAmount);

	if (distance > LabelViewAmount)
	{
		label->SetVisibility(ESlateVisibility::Collapsed);

		return;
	}

	label->SetVisibility(ESlateVisibility::Visible);
	label->SetRenderScale(FVector2D(sizeRate, sizeRate));
}

void ACEnemy_AI::Hitted()
{
	Super::Hitted();
	CheckTrue(State->IsDeadMode());

	Behavior->SetHittedMode();
}

void ACEnemy_AI::End_Hitted()
{
	Super::End_Hitted();

	Behavior->SetWaitMode();
}