// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeWidget.h"

#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"

void UFadeWidget::Tick(float DeltaTime)
{
	if(bIsFading)
	{
		CurrentFadeTime += DeltaTime;

		Alpha = UKismetMathLibrary::FInterpTo_Constant(Alpha, 1.0f, DeltaTime, (1.0f - Alpha) / FadeTime);

		UpdateFadeImageAlpha();

		if(Alpha + UE_KINDA_SMALL_NUMBER >= 1.0f)
		{
			OnFadeEnd.Broadcast(false);
			bIsFading = false;
		}
	}
	else
	{
		Alpha = UKismetMathLibrary::FInterpTo_Constant(Alpha, 0.0f, DeltaTime, (1.0f - Alpha) / 2.0f);

		UpdateFadeImageAlpha();
	}
}

void UFadeWidget::TriggerFade()
{
	bIsFading = true;
	CurrentFadeTime = 0.0f;
	Alpha = 0.0f;
	UpdateFadeImageAlpha();
}

void UFadeWidget::ResetFade()
{
	bIsFading = false;
	CurrentFadeTime = 0.0f;
	UpdateFadeImageAlpha();
}

void UFadeWidget::UpdateFadeImageAlpha()
{
	if(FadeImage)
	{
		auto CurrentColorAndOpacity = FadeImage->ColorAndOpacity;
		CurrentColorAndOpacity.A = Alpha;
		
		FadeImage->SetColorAndOpacity(CurrentColorAndOpacity);
	}
}
