// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "LightInteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInteractableChange, ULightInteractableComponent*, Context, bool, bWasLit);

class UOverheadWidget;
class UWidgetComponent;
class UPointLightComponent;
class ADMGameJam20231Character;

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

	bool Interact(ADMGameJam20231Character* Character);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetLuminanceValue() const { return LuminanceValue; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool IsLit() const { return bIsLit; }

	FInteractableChange OnChange;

private:
	UPROPERTY(EditAnywhere)
	bool bDefaultLitStatus = false;

	UPROPERTY(VisibleAnywhere)
	bool bIsLit = false;
	
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

	UPROPERTY(EditAnywhere)
	float LuminanceValue = 0.2f;

	void SetInteractableVisibility() const;
	void SetOverheadWidgetText(const FString& InText);
};
