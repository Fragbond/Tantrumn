// Fill out your copyright notice in the Description page of Project Settings.


#include "WallInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InteractionComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TextRenderComponent.h"
#include "TantrumnCharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "TantrumnCharacterBase.h"

constexpr float FLT_METERS(float meters) { return meters * 100.0f; }

static TAutoConsoleVariable<bool> CVarToggleDebugDoor(
	TEXT("Tantrumn.WallInteractionComponent.Debug"),
	false,
	TEXT("Toggle WallInteractionComponent debug display."),
	ECVF_Default);

// Sets default values for this component's properties
UWallInteractionComponent::UWallInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWallInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	//if (HasAuthority())
	//{
		StartRotation = GetOwner()->GetActorRotation();
		FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
		//ensure TimeToRotate is greater than EPSILON
		CurrentRotationTime = 0.0f;
		//check(AudioComponent);
	//}
}


// Called every frame
void UWallInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if (HasAuthority())
	//{
		if (CurrentRotationTime < TimeToRotate)
		{
			if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
			{
				APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
				if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
				{
					CurrentRotationTime += DeltaTime;
					const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
					const FRotator CurrentRoation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
					GetOwner()->SetActorRotation(CurrentRoation);
				}
			}
		}
	//}
}

//bool UWallInteractionComponent::HasAuthority() const
//{
	//return (GetLocalRole() == ROLE_Authority);
//}