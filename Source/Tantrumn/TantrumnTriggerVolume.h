// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "TantrumnTriggerVolume.generated.h"

class ATantrumnGameModeBase;

UCLASS()
class TANTRUMN_API ATantrumnTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
public:

	ATantrumnTriggerVolume();

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	ATantrumnGameModeBase* GameModeRef;
};
