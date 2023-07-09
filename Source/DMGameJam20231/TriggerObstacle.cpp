// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerObstacle.h"

#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATriggerObstacle::ATriggerObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	BlockingParticlesComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BlockingParticles"));
	BlockingParticlesComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATriggerObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerObstacle::Interact()
{
	if(ParticlesActivated)
	{
		BlockingParticlesComponent->Deactivate();
		ParticlesActivated = false;
	}
	else
	{
		BlockingParticlesComponent->ActivateSystem(false);
		ParticlesActivated = true;
	}
	
	CollisionBox->SetCollisionEnabled(CollisionBox->GetCollisionEnabled() == ECollisionEnabled::NoCollision ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}

