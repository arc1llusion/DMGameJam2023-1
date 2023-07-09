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
	
	UE_LOG(LogTemp, Warning, TEXT("Initialize Game Mode"));
	
	Character = Cast<ADMGameJam20231Character>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if(Character)
	{
		Character->OnLuminanceEmpty.AddDynamic(this, &ADMGameJam20231GameMode::OnCharacterLuminanceEmpty);
		Character->OnLuminanceAdded.AddDynamic(this, &ADMGameJam20231GameMode::OnCharacterLuminanceAdded);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character not found"));
	}

	if(FadeWidgetClass)
	{
		FadeWidget = Cast<UFadeWidget>(CreateWidget(GetWorld(), FadeWidgetClass, TEXT("FadeWidget") ));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fade Widget class Missing"));
	}

	if(FadeWidget)
	{
		FadeWidget->AddToViewport();
		FadeWidget->OnFadeEnd.AddDynamic(this, &ADMGameJam20231GameMode::OnFadeEnd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fade Widget not created"));
	}
}

void ADMGameJam20231GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(FadeWidget)
	{
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
	UE_LOG(LogTemp, Warning, TEXT("Trigger Fade"));
	if(FadeWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fade found"));
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
