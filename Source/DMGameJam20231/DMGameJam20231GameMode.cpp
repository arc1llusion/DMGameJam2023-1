// Copyright Epic Games, Inc. All Rights Reserved.

#include "DMGameJam20231GameMode.h"
#include "DMGameJam20231Character.h"
#include "UObject/ConstructorHelpers.h"

ADMGameJam20231GameMode::ADMGameJam20231GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
