// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TantrumnGameModeBase.h"
#include "Sound/SoundCue.h"
#include "TantrumnPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANTRUMN_API ATantrumnPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	virtual void ReceivedPlayer() override;
protected:
	void SetupInputComponent() override;

	void RequestJump();
	void RequestStopJump();

	void RequestRun();
	void RequestStopRunning();

	void RequestCrouch();
	void RequestUnCrouch();

	void RequestMoveForward(float AxisValue);
	void RequestMoveRight(float AxisValue);
	void RequestLookUp(float AxisValue);
	void RequestLookRight(float AxisValue);
	void RequestThrowObject(float AxisValue);

	void RequestPullObject();
	void RequestStopPullObject();

	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY()
		UUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere, Category = "Look")
		float BaseLookUpRate = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Look")
		float BaseLookRightRate = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float RunningSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, Category = "Input")
		float FlickThreshold = 0.75f;

	float LastAxis = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* JumpSound = nullptr;

	ATantrumnGameModeBase* GameModeRef;

};
