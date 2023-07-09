// Copyright Epic Games, Inc. All Rights Reserved.

#include "DMGameJam20231Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LightInteractableComponent.h"
#include "Components/PointLightComponent.h"



//////////////////////////////////////////////////////////////////////////
// ADMGameJam20231Character

ADMGameJam20231Character::ADMGameJam20231Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//RootComponent->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;

	SpriteLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("SpriteLight"));
	SpriteLight->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CurrentLuminance = MaxLuminance;
	MaxPointLightIntensity = SpriteLight->Intensity;
}

void ADMGameJam20231Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ADMGameJam20231Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SpriteParticles = FindComponentByClass<UNiagaraComponent>();
}

void ADMGameJam20231Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);	
	
	CameraBoom->AddRelativeRotation(FRotator(0.0f, RotationToAdd.Yaw * DeltaSeconds * RotationRate, 0.0f));
	RotationToAdd = FRotator::ZeroRotator;
}

void ADMGameJam20231Character::SetLightInteractable(ULightInteractableComponent* InLightInteractable)
{
	CurrentInteractable = InLightInteractable;
}

//////////////////////////////////////////////////////////////////////////
// Input


void ADMGameJam20231Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		//Moving
		EnhancedInputComponent->BindAction(MoveActionAsset, ETriggerEvent::Triggered, this, &ADMGameJam20231Character::MoveAction);

		//Looking
		EnhancedInputComponent->BindAction(LookActionAsset, ETriggerEvent::Triggered, this, &ADMGameJam20231Character::LookAction);

		//Interact
		EnhancedInputComponent->BindAction(InteractActionAsset, ETriggerEvent::Started, this, &ADMGameJam20231Character::InteractAction);
	}
}

void ADMGameJam20231Character::MoveAction(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = CameraBoom->GetRelativeRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADMGameJam20231Character::LookAction(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	RotationToAdd += FRotator(0.0f, LookAxisVector.X, 0.0f);
}

void ADMGameJam20231Character::InteractAction(const FInputActionValue& Value)
{
	if(CurrentInteractable)
	{
		const bool bLit = CurrentInteractable->IsLit();

		if(!bLit && CurrentInteractable->GetLuminanceValue() <= CurrentLuminance)
		{
			CurrentInteractable->Interact();
			CurrentLuminance -= CurrentInteractable->GetLuminanceValue();
		}
		else if(bLit)
		{
			CurrentInteractable->Interact();
			CurrentLuminance += CurrentInteractable->GetLuminanceValue();

			OnLuminanceAdded.Broadcast();
		}

		if(SpriteLight)
		{
			SpriteLight->SetIntensity(MaxPointLightIntensity * CurrentLuminance);
		}

		if(CurrentLuminance <= SMALL_NUMBER)
		{
			OnLuminanceEmpty.Broadcast();
		}

		if(SpriteParticles)
		{
			SpriteParticles->SetNiagaraVariableFloat("SpawnRate", MaxNiagaraSpawnRate * CurrentLuminance);
		}

		UE_LOG(LogTemp, Warning, TEXT("Luminance: %f"), CurrentLuminance);
	}
}



