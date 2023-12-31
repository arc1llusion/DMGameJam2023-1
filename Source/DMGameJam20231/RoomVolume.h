// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomVolume.generated.h"

class ATriggerObstacle;
class ULightInteractableComponent;
class UBoxComponent;

UCLASS()
class DMGAMEJAM20231_API ARoomVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void InteractableChanged(ULightInteractableComponent* Context, bool bWasLit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetLuminanceRatio() const { return LuminanceRatio; }

private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(EditAnywhere)
	float TriggerRatioThreshold = 0.5f;

	UPROPERTY(EditAnywhere)
	TArray<ATriggerObstacle*> Obstacles;

	TArray<ULightInteractableComponent*> InteractableComponentsInVolume;

	float LuminanceRatio = 0.0f;

	void CalculateLuminanceRatio();
};
