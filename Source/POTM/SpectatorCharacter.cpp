// Fill out your copyright notice in the Description page of Project Settings.

#include "POTM.h"
#include "SpectatorCharacter.h"


// Sets default values
ASpectatorCharacter::ASpectatorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bIsJogging = false;
	JoggingDirection = 0.0f;
	bIsCrouching = false;
	bIsJumping = false;

	// Create a camera component to handle viewing the scene
	SpectatorCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SpectatorCamera"));
	// Set the default location and rotation of the camera
	SpectatorCamera->SetRelativeLocationAndRotation(FVector(70.0f, 10.0f, 30.0f), FRotator(20.0f, -180.0f, 0.0f));
	// Attach the camera to the camera boom
	SpectatorCamera->AttachTo(GetCapsuleComponent(), USpringArmComponent::SocketName);

	SpectatorName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("SpectatorName"));
	SpectatorName->AttachTo(GetCapsuleComponent());
	SpectatorName->SetVisibility(false);

}

// Called when the game starts or when spawned
void ASpectatorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpectatorCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bIsJogging)
	{
		MoveForward(JoggingDirection);
	}

}

// Called to bind functionality to input
void ASpectatorCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

// Handles the event when the MoveForward buttons are pressed
void ASpectatorCharacter::MoveForward(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Movement Pressed AxisValue = %f:"), AxisValue);

		AddMovementInput(GetActorForwardVector(), AxisValue);
	}
}

void ASpectatorCharacter::JogStarted(float Direction)
{
	bIsJogging = true;
	JoggingDirection = Direction;
}
void ASpectatorCharacter::JogStopped()
{
	bIsJogging = false;
	JoggingDirection = 0.0f;
}

void ASpectatorCharacter::CrouchingStarted()
{
	bIsCrouching = true;
}
void ASpectatorCharacter::CrouchingStopped()
{
	bIsCrouching = false;
}

void ASpectatorCharacter::JumpingStarted()
{
	bIsJumping = true;
}
void ASpectatorCharacter::JumpingStopped()
{
	bIsJumping = false;
}

void ASpectatorCharacter::DisplayName(bool isDisplayed)
{
	SpectatorName->SetVisibility(isDisplayed);
}

