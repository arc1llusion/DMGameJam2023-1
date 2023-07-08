// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomVolume.h"

#include "LightInteractableComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ARoomVolume::ARoomVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomVolume"));
	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void ARoomVolume::BeginPlay()
{
	Super::BeginPlay();

	TArray<UPrimitiveComponent*> Components;
	GetOverlappingComponents(Components);

	for(const auto OverlappedComponent : Components)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped Component: %s"), *OverlappedComponent->GetName());
		if(const auto InteractableComponent = Cast<ULightInteractableComponent>(OverlappedComponent))
		{
			InteractableComponentsInVolume.Add(InteractableComponent);

			InteractableComponent->OnChange.AddDynamic(this, &ARoomVolume::InteractableChanged);
		}
	}

	CalculateLuminanceRatio();
}

void ARoomVolume::InteractableChanged(ULightInteractableComponent* Context, bool bWasLit)
{
	CalculateLuminanceRatio();
}

// Called every frame
void ARoomVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoomVolume::CalculateLuminanceRatio()
{
	float TotalLuminance = 0.0f;
	float ActivatedLuminance = 0.0f;
	for(const auto InteractableComponent : InteractableComponentsInVolume)
	{
		if(InteractableComponent->IsLit())
		{
			ActivatedLuminance += InteractableComponent->GetLuminanceValue();
		}

		TotalLuminance += InteractableComponent->GetLuminanceValue();
	}

	LuminanceRatio = ActivatedLuminance <= 0.0f ? 0.0f : (ActivatedLuminance / TotalLuminance);

	UE_LOG(LogTemp, Warning, TEXT("Room Luminance Ratio: %f"), LuminanceRatio);
}

