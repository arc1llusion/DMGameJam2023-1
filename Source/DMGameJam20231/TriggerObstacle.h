// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerObstacle.generated.h"

class UNiagaraComponent;
class UBoxComponent;

UCLASS()
class DMGAMEJAM20231_API ATriggerObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact();

private:
	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* BlockingParticlesComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	bool ParticlesActivated = true;
};
