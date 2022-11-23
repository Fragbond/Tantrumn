// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "TantrumnGameWidget.h"
#include "TantrumnGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	NONE		UMETA(DisplayName = "NONE"),
	Waiting		UMETA(DisplayName = "Waiting"),
	Playing		UMETA(DisplayName = "Playing"),
	Paused		UMETA(DisplayName = "Paused"),
	GameOver	UMETA(DisplayName = "GameOver"),
};

UCLASS()
class TANTRUMN_API ATantrumnGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ATantrumnGameModeBase();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const;

	void PlayerReachedEnd();

private:

	UPROPERTY(VisibleAnywhere,Category = "States")
	EGameState CurrentGameState = EGameState::NONE;

	UPROPERTY(EditAnywhere, Category = "Game Details")
	float GameCountdownDuration = 4.0f;

	FTimerHandle TimerHandle;

	UPROPERTY()
	UTantrumnGameWidget* GameWidget;
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UTantrumnGameWidget> GameWidgetClass;

	APlayerController* PC = nullptr;

	void DisplayCountdown();
	void StartGame();
};
