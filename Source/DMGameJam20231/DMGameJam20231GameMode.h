// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DMGameJam20231GameMode.generated.h"

class UUserWidget;
class UFadeWidget;
class ADMGameJam20231Character;

UCLASS(minimalapi)
class ADMGameJam20231GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADMGameJam20231GameMode();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCharacterLuminanceAdded();
	
	UFUNCTION()
	void OnCharacterLuminanceEmpty();
	
	UFUNCTION()
	void OnFadeEnd(bool bIsReset);

public:
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY()
	ADMGameJam20231Character* Character;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> FadeWidgetClass;

	UPROPERTY()
	UFadeWidget* FadeWidget;

	UPROPERTY(EditAnywhere)
	FName LevelToLoadOnLose{TEXT("M_Level_01")};
};



