// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFadeEnd, bool, bIsReset);

class UImage;

/**
 * 
 */
UCLASS()
class DMGAMEJAM20231_API UFadeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UImage* FadeImage;

	void Tick(float DeltaTime);

	void TriggerFade();
	void ResetFade();

	FFadeEnd OnFadeEnd;
	
private:
	UPROPERTY(EditAnywhere)
	float FadeTime = 30.0f;

	float CurrentFadeTime = 0.0f;

	float Alpha = 0.0f;

	bool bIsFading = false;

	void UpdateFadeImageAlpha();
};
