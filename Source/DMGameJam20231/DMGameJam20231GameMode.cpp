// Copyright Epic Games, Inc. All Rights Reserved.

#include "DMGameJam20231GameMode.h"
#include "DMGameJam20231Character.h"
#include "FadeWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ADMGameJam20231GameMode::ADMGameJam20231GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ADMGameJam20231GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	Character = Cast<ADMGameJam20231Character>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if(Character)
	{
		Character->OnLuminanceEmpty.AddDynamic(this, &ADMGameJam20231GameMode::OnCharacterLuminanceEmpty);
		Character->OnLuminanceAdded.AddDynamic(this, &ADMGameJam20231GameMode::OnCharacterLuminanceAdded);
	}	

	if(FadeWidgetClass)
	{
		FadeWidget = Cast<UFadeWidget>(CreateWidget(GetWorld(), FadeWidgetClass, TEXT("FadeWidget") ));
	}

	if(FadeWidget)
	{
		FadeWidget->AddToViewport();
		FadeWidget->OnFadeEnd.AddDynamic(this, &ADMGameJam20231GameMode::OnFadeEnd);
	}
}

void ADMGameJam20231GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(FadeWidget)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Game Mode Tick"));
		FadeWidget->Tick(DeltaSeconds);
	}
}

void ADMGameJam20231GameMode::OnCharacterLuminanceAdded()
{
	if(FadeWidget)
	{
		FadeWidget->ResetFade();
	}
}

void ADMGameJam20231GameMode::OnCharacterLuminanceEmpty()
{
	if(FadeWidget)
	{
		FadeWidget->TriggerFade();
	}
}

void ADMGameJam20231GameMode::OnFadeEnd(bool bIsReset)
{
	if(bIsReset)
	{
		FadeWidget->RemoveFromParent();
	}
}
