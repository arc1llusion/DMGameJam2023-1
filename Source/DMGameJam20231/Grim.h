// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grim.generated.h"


class USoundCue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DMGAMEJAM20231_API UGrim : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrim();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void PlaySound();
	
private:
	FTimerHandle SoundTimerHandle;
	FTimerDelegate SoundTimerDelegate;

	UPROPERTY(EditAnywhere)
	USoundCue* Sounds;

	UPROPERTY(EditAnywhere)
	float SoundMinTime = 10.0f;

	UPROPERTY(EditAnywhere)
	float SoundMaxTime = 25.0f;
};
