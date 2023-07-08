// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "DMGameJam20231Character.generated.h"


class UPointLightComponent;
class ULightInteractableComponent;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS(config=Game)
class ADMGameJam20231Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Light, meta = (AllowPrivateAccess = "true"))
	UPointLightComponent* SpriteLight;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveActionAsset;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookActionAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractActionAsset;

public:
	ADMGameJam20231Character();
	

protected:

	/** Called for movement input */
	void MoveAction(const FInputActionValue& Value);

	/** Called for looking input */
	void LookAction(const FInputActionValue& Value);

	void InteractAction(const FInputActionValue& Value);
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void SetLightInteractable(ULightInteractableComponent* InLightInteractable);
	
private:
	UPROPERTY(EditAnywhere, Category = "Luminance")
	float MaxLuminance = 1.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Luminance")
	float CurrentLuminance;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float MaxInteractDistance = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float MaxInteractRadius = 100.0f;

	float MaxPointLightIntensity = 0.0f;

	FRotator RotationToAdd;

	UPROPERTY(EditAnywhere)
	float RotationRate = 500.0f;

	UPROPERTY()
	ULightInteractableComponent* CurrentInteractable;
};

