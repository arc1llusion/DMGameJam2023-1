// Fill out your copyright notice in the Description page of Project Settings.


#include "LightInteractableComponent.h"

#include "DMGameJam20231Character.h"
#include "OverheadWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"

ULightInteractableComponent::ULightInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void ULightInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	// Try to get the objects anyway if not assigned
	if(!PointLight || !Particles || !StaticMeshComponent)
	{
		const USceneComponent* RootComponent = GetOwner()->GetRootComponent();
		TArray<USceneComponent*> Components;
		
		RootComponent->GetChildrenComponents(false, Components);

		for(const auto Child : Components)
		{			
			if(!PointLight)
			{
				if(const auto PointLightChild = Cast<UPointLightComponent>(Child))
				{
					PointLight = PointLightChild;
				}
			}
			
			if(!Particles)
			{
				if(const auto ParticleChild = Cast<UParticleSystemComponent>(Child))
				{
					Particles = ParticleChild;
				}
			}

			if(!StaticMeshComponent)
			{
				if(const auto StaticMeshChild = Cast<UStaticMeshComponent>(Child))
				{
					StaticMeshComponent = StaticMeshChild;
				}
			}

			if(!WidgetComponent)
			{
				if(const auto WidgetComponentChild = Cast<UWidgetComponent>(Child))
				{
					WidgetComponent = WidgetComponentChild;
				}
			}
		}
	}

	if(WidgetComponent)
	{
		if(const auto OverheadWidgetChild = Cast<UOverheadWidget>(WidgetComponent->GetWidget()))
		{
			OverheadWidget = OverheadWidgetChild;
		}
	}

	OnComponentBeginOverlap.AddDynamic(this, &ULightInteractableComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ULightInteractableComponent::OnEndOverlap);

	Lit = DefaultLitStatus;
	if(PointLight)
	{
		PointLight->SetVisibility(DefaultLitStatus, false);
	}
	
	if(Particles)
	{
		Particles->SetVisibility(DefaultLitStatus, false);
	}
}

void ULightInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void ULightInteractableComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(const auto Character = Cast<ADMGameJam20231Character>(OtherActor))
	{
		Character->SetLightInteractable(this);
		
		if(StaticMeshComponent)
		{
			StaticMeshComponent->SetRenderCustomDepth(true);
		}

		if(OverheadWidget)
		{
			OverheadWidget->SetDisplayText(Lit ? TEXT("Press E to Extinguish") : TEXT("Press E to Light"));
		}
	}	
}

void ULightInteractableComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(const auto Character = Cast<ADMGameJam20231Character>(OtherActor))
	{
		Character->SetLightInteractable(nullptr);

		if(StaticMeshComponent)
		{
			StaticMeshComponent->SetRenderCustomDepth(false);
		}

		if(OverheadWidget)
		{
			OverheadWidget->SetDisplayText(TEXT(""));
		}
	}
}

void ULightInteractableComponent::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction succeeded"));

	Lit = !Lit;

	if(PointLight)
	{
		PointLight->SetVisibility(Lit, false);
	}
	
	if(Particles)
	{
		Particles->SetVisibility(Lit, false);
	}

	if(OverheadWidget)
	{
		OverheadWidget->SetDisplayText(Lit ? TEXT("Press E to Extinguish") : TEXT("Press E to Light"));
	}
}
