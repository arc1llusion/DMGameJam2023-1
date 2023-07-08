// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "LightInteractableComponent.generated.h"

class UOverheadWidget;
class UWidgetComponent;
class UPointLightComponent;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DMGAMEJAM20231_API ULightInteractableComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	ULightInteractableComponent();

protected:	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void Interact();

private:
	UPROPERTY(EditAnywhere)
	bool DefaultLitStatus = false;

	UPROPERTY(VisibleAnywhere)
	bool Lit = false;
	
	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* Particles;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* WidgetComponent;

	UPROPERTY()
	UOverheadWidget* OverheadWidget; 
};
