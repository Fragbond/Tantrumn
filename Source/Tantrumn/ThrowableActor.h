// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "ThrowableActor.generated.h"

class UStaticMeshCompnent;
class UProjectileMovementComponent;

UCLASS()
class TANTRUMN_API AThrowableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableActor();

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool IsIdle() const { return State == EState::Idle; }

	UFUNCTION(BlueprintCallable)
	bool Pull(AActor* InActor);

	UFUNCTION(BlueprintCallable)
	void Launch(const FVector& IntitialVelocity, AActor* Target = nullptr);

	UFUNCTION(BlueprintCallable)
	void Drop();

	UFUNCTION(BlueprintCallable)
	void ToggleHighlight(bool bIsOn);

	EEffectType GetEffectType();

protected:
	enum class EState
	{
		Idle,
		Pull,
		Attached,
		Launch,
		Dropped,
	};

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION()
	void ProjectileStop(const FHitResult& ImpactResult);

	UFUNCTION()
	bool SetHomingTarget(AActor* Target);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	EState State = EState::Idle;

	UPROPERTY()
	AActor* PullActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effect")
	EEffectType EffectType = EEffectType::None;
};
