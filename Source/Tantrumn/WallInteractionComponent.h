// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "WallInteractionComponent.generated.h"

class ATriggerBox;
class IConsoleVariable;
class AActor;

UENUM()
enum class EDoorState
{
	DS_Closed = 0 UMETA(DisplayName = "Closed"),
	DS_Opening = 1 UMETA(DispalyName = "Opening"),
	DS_Open = 2 UMETA(DisplayName = "Open"),
	DS_Locked = 3 UMETA(DisplayName = "Locked"),
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANTRUMN_API UWallInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()

public:
	UWallInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//bool HasAuthority() const;

	UPROPERTY(EditAnywhere)
		FRotator DesiredRotation = FRotator::ZeroRotator;

	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
		float TimeToRotate = 1.0f;

	float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere)
		ATriggerBox* TriggerBox;

	//UFUNCTION(BlueprintCallable, Category = Replication)
		//ENetRole GetLocalRole() const { return Role; }
private:
	//UPROPERTY(Replicated)
		//TEnumAsByte<enum ENetRole> Role;
};
