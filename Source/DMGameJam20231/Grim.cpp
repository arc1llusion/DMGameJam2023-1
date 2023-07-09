// Fill out your copyright notice in the Description page of Project Settings.


#include "Grim.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values for this component's properties
UGrim::UGrim()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrim::BeginPlay()
{
	Super::BeginPlay();

	if(const auto World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();

		if(!SoundTimerDelegate.IsBound())
		{
			SoundTimerDelegate.BindUFunction(this, "PlaySound");
		}
		
		TimerManager.SetTimer(SoundTimerHandle, SoundTimerDelegate, FMath::RandRange(SoundMinTime, SoundMaxTime), false, FMath::RandRange(SoundMinTime, SoundMaxTime));
	}	
}


// Called every frame
void UGrim::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// if(Sounds && Sounds->AttenuationSettings)
	// {		
	// 	DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), Sounds->AttenuationSettings->Attenuation.AttenuationShapeExtents.X, 12, FColor::Red);
	// 	DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), Sounds->AttenuationSettings->Attenuation.FalloffDistance, 12, FColor::Blue);
	// }
}

void UGrim::PlaySound()
{
	if(Sounds)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sounds, GetOwner()->GetActorLocation());
	}
	
	if(const auto World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();		
		TimerManager.SetTimer(SoundTimerHandle, SoundTimerDelegate, FMath::RandRange(SoundMinTime, SoundMaxTime), false, FMath::RandRange(SoundMinTime, SoundMaxTime));
	}	
}

