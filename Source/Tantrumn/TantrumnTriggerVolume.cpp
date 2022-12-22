// Fill out your copyright notice in the Description page of Project Settings.


#include "TantrumnTriggerVolume.h"
#include "TantrumnCharacterBase.h"
#include "TantrumnGameModeBase.h"

ATantrumnTriggerVolume::ATantrumnTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &ATantrumnTriggerVolume::OnOverlapBegin);
}

void ATantrumnTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = GetWorld()->GetAuthGameMode<ATantrumnGameModeBase>();
}

void ATantrumnTriggerVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ATantrumnCharacterBase* TantrumnCharacterBase = Cast<ATantrumnCharacterBase>(OtherActor))
	{
		APlayerController* PlayerController = TantrumnCharacterBase->GetController<APlayerController>();
		GameModeRef->PlayerReachedEnd(PlayerController);
	}
}
