// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "TantrumnCharacterBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//creating the trigger capsule
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	//binding to events
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnOverlapEnd);

	InteractingActor = nullptr;
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	ATantrumnCharacterBase* Player = Cast<ATantrumnCharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		//bind to player input
		Player->OnInteractionStart.AddUObject(this, &UInteractionComponent::InteractionStart);
	}
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (InteractingActor)
	{
		FVector Offset(0.0f, 0.0f, 100.0f);
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		DrawDebugString(GetWorld(), Offset, InteractionPrompt.ToString(), GetOwner(), FColor::Blue, 0.0f);
	}
}

void UInteractionComponent::InteractionStart()
{

}

