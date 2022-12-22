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

	void PlayerReachedEnd(APlayerController* PlayerController);
	void ReceivePlayer(APlayerController* PlayerController);

private:

	UPROPERTY(VisibleAnywhere,Category = "States")
	EGameState CurrentGameState = EGameState::NONE;

	UPROPERTY(EditAnywhere, Category = "Game Details")
	float GameCountdownDuration = 4.0f;

	UFUNCTION(BlueprintCallable, Category = "Game Details")
		void SetNumExpectedPlayers(uint8 InNumExpectedPlayers) { NumExpectedPlayers = InNumExpectedPlayers; }

	UPROPERTY(EditAnywhere, Category = "Game Details")
		uint8 NumExpectedPlayers = 1u;

	FTimerHandle TimerHandle;

	UPROPERTY()
	TMap<APlayerController*, UTantrumnGameWidget*> GameWidgets;
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UTantrumnGameWidget> GameWidgetClass;

	APlayerController* PC = nullptr;

	void DisplayCountdown();
	void StartGame();
	void AttemptStartGame();
};
