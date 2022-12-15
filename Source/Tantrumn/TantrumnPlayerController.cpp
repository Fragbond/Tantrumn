// Fill out your copyright notice in the Description page of Project Settings.


#include "TantrumnPlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TantrumnCharacterBase.h"
#include "TantrumnGameModeBase.h"


static TAutoConsoleVariable<bool> CVarDisplayLaunchInputDelta(
	TEXT("Tantrumn.Character.Debug.DisplayLaunchInputDelta"),
	false,
	TEXT("Display Launch Input Delta"),
	ECVF_Default);

void ATantrumnPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<ATantrumnGameModeBase>(GetWorld()->GetAuthGameMode());
}

void ATantrumnPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ATantrumnPlayerController::RequestJump);
		InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ATantrumnPlayerController::RequestStopJump);

		InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &ATantrumnPlayerController::RequestRun);
		InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &ATantrumnPlayerController::RequestStopRunning);

		InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ATantrumnPlayerController::RequestCrouch);
		InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &ATantrumnPlayerController::RequestUnCrouch);

		InputComponent->BindAxis(TEXT("Foward"), this, &ATantrumnPlayerController::RequestMoveForward);
		InputComponent->BindAxis(TEXT("MoveRight"), this, &ATantrumnPlayerController::RequestMoveRight);
		InputComponent->BindAxis(TEXT("LookUp"), this, &ATantrumnPlayerController::RequestLookUp);
		InputComponent->BindAxis(TEXT("TurnRight"), this, &ATantrumnPlayerController::RequestLookRight);
		InputComponent->BindAxis(TEXT("ThrowObject"), this, &ATantrumnPlayerController::RequestThrowObject);

		InputComponent->BindAction(TEXT("PullObject"), EInputEvent::IE_Pressed, this, &ATantrumnPlayerController::RequestPullObject);
		InputComponent->BindAction(TEXT("PullObject"), EInputEvent::IE_Released, this, &ATantrumnPlayerController::RequestStopPullObject);
	}
}

void ATantrumnPlayerController::RequestJump()
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (GetCharacter())
	{
		GetCharacter()->Jump();

		if (JumpSound && GetCharacter()->GetCharacterMovement()->IsMovingOnGround())
		{
			FVector CharacterLocation = GetCharacter()->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(this, JumpSound, CharacterLocation);
		}
	}
}

void ATantrumnPlayerController::RequestMoveForward(float AxisValue)
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (AxisValue != 0.f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), AxisValue);
	}
}

void ATantrumnPlayerController::RequestMoveRight(float AxisValue)
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (AxisValue != 0.f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), AxisValue);
	}
}

void ATantrumnPlayerController::RequestLookUp(float AxisValue)
{
	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATantrumnPlayerController::RequestLookRight(float AxisValue)
{
	AddYawInput(AxisValue * BaseLookRightRate * GetWorld()->GetDeltaSeconds());
}

void ATantrumnPlayerController::RequestRun()
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (GetCharacter())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed += RunningSpeed;
	}
}

void ATantrumnPlayerController::RequestCrouch()
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (GetCharacter())
	{
		GetCharacter()->Crouch();
	}
}

void ATantrumnPlayerController::RequestUnCrouch()
{
	if (GetCharacter())
	{
		GetCharacter()->UnCrouch();
	}
}

void ATantrumnPlayerController::RequestStopRunning()
{
	if (GetCharacter())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed -= RunningSpeed;
	}
}

void ATantrumnPlayerController::RequestStopJump()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void ATantrumnPlayerController::RequestPullObject()
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (ATantrumnCharacterBase* TantrumnCharacterBase = Cast<ATantrumnCharacterBase>(GetCharacter()))
	{
		TantrumnCharacterBase->RequestPullObject();
	}
}

void ATantrumnPlayerController::RequestStopPullObject()
{
	if (ATantrumnCharacterBase* TantrumnCharacterBase = Cast<ATantrumnCharacterBase>(GetCharacter()))
	{
		TantrumnCharacterBase->RequestStopPullObject();
	}
}

void ATantrumnPlayerController::RequestThrowObject(float AxisValue)
{
	if (!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }
	if (ATantrumnCharacterBase* TantrumnCharacterBase = Cast<ATantrumnCharacterBase>(GetCharacter()))
	{
		if (TantrumnCharacterBase->CanThrowObject())
		{
			float currentDelta = AxisValue - LastAxis;

			//debug
			if (CVarDisplayLaunchInputDelta->GetBool())
			{
				if (fabs(currentDelta) > 0.0f)
				{
					UE_LOG(LogTemp, Warning, TEXT("Axis: %f LastAxis: %f currentDelta: %f"), AxisValue, LastAxis);
				}
			}
			LastAxis = AxisValue;
			const bool IsFlick = fabs(currentDelta) > FlickThreshold;
			if (IsFlick)
			{
				if (AxisValue > 0)
				{
					TantrumnCharacterBase->RequestThrowObject();
				}
				else
				{
					TantrumnCharacterBase->RequestUseObject();
				}
			}
		}
		else
		{
			LastAxis = 0.0f;
		}
	}
}
