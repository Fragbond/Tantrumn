// Fill out your copyright notice in the Description page of Project Settings.


#include "TantrumnTriggerVolume.h"
#include "TantrumnCharacterBase.h"
#include "TantrumnGameStateBase.h"

ATantrumnTriggerVolume::ATantrumnTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &ATantrumnTriggerVolume::OnOverlapBegin);
}

void ATantrumnTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}

void ATantrumnTriggerVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HasAuthority())
	{
		if (ATantrumnGameStateBase* TantrumnGameState = GetWorld()->GetGameState<ATantrumnGameStateBase>())
		{
			ATantrumnCharacterBase* TantrumnCharacterBase = Cast<ATantrumnCharacterBase>(OtherActor);
			TantrumnGameState->OnPlayerReachedEnd(TantrumnCharacterBase);
		}
	}

}
