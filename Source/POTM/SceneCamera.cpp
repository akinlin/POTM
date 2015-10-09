// Fill out your copyright notice in the Description page of Project Settings.

#include "POTM.h"
#include "SceneCamera.h"


// Sets default values
ASceneCamera::ASceneCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default the references to the scene actors to null for view handling
	SpectatorCharacter_0 = nullptr;
	SpectatorCharacter_1 = nullptr;

	// Create the capsule component that will repersent the cameraman
	Root = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));

	// Create the camera spring arm that will act as the camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// Attach it to the root capsule component
	CameraBoom->AttachTo(Root);
	// Set a default arm lenght
	CameraBoom->TargetArmLength = 100.0f;

	// Create a camera component to handle viewing the scene
	SceneCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SceneCamera"));
	// Attach the camera to the camera boom
	SceneCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName);

	// The default destination for the camera is the actor starting location
	CameraDestination = GetActorLocation();
	// The velocity is determined by calculating the direction of movement since there is no movement set it to ZERO
	CameraVelocity = FVector::ZeroVector;
	CameraSpeed = 100.0f;

}

// Called when the game starts or when spawned
void ASceneCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update where the camera should be located
	UpdateCameraDestination();

	// Zoom the camera
	{
		// TODO: REVIEW the zooming methods need to be reworked a bit now that this function is known
		float ZoomScale = FMath::GetRangePct(400.0f, 200.0f, SpectatorDistance.Y);
		UE_LOG(LogTemp, Warning, TEXT("ZoomScale: %f"), ZoomScale);
		if (bZoomingIn)
		{
			ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
		SceneCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		CameraBoom->TargetArmLength = FMath::Lerp<float>(100.0f, 50.0f, ZoomScale);
	}

	// Move the camera
	{
		// Move the camera if it is not yet at its destination
		FVector CameraLocation = GetActorLocation();
		if (CameraDestination.Y != CameraLocation.Y)
		{
			//UE_LOG(LogTemp, Warning, TEXT("CameraDestination: %f"), CameraDestination.X);
			//UE_LOG(LogTemp, Warning, TEXT("CameraLocation: %f"), CameraLocation.X);
			// Update the location in the direction of the velocity at the rate of the speed
			FVector UpdatedLocation = FVector::ZeroVector;
			UpdatedLocation.Y = CameraLocation.Y + ((CameraSpeed * DeltaTime) * CameraVelocity.Y);
			// Check if the update moved it past its destination
			if (CameraVelocity.Y > 0)
			{
				// Check if overshot destination
				if (UpdatedLocation.Y > CameraDestination.Y)
				{
					UpdatedLocation = CameraDestination;
				}
			}
			else
			{
				// Check if undershot destination
				if (UpdatedLocation.Y < CameraDestination.Y)
				{
					UpdatedLocation = CameraDestination;
				}
			}

			// Update the camera to the new location
			CameraLocation.Y = UpdatedLocation.Y;
			SetActorLocation(CameraLocation);
		}
	}

}

void ASceneCamera::UpdateCameraDestination()
{
	// Set the camera destination if spectator characters have been set
	if (SpectatorCharacter_0 || SpectatorCharacter_1)
	{
		if (SpectatorCharacter_0 && SpectatorCharacter_1)
		{
			// Both characters are set calulate the midpoint between them as the camera destination
			// Figure out who is on the left and who is on the right
			FVector SpectatorLocation_0 = SpectatorCharacter_0->GetActorLocation();
			//UE_LOG(LogTemp, Warning, TEXT("SpectatorLocation_0: %f"), SpectatorLocation_0.Y);
			FVector SpectatorLocation_1 = SpectatorCharacter_1->GetActorLocation();
			//UE_LOG(LogTemp, Warning, TEXT("SpectatorLocation_1: %f"), SpectatorLocation_1.Y);
			FVector SpectatorLocationLeft = FVector::ZeroVector;
			FVector SpectatorLocationRight = FVector::ZeroVector;

			if (SpectatorLocation_0.Y > SpectatorLocation_1.Y)
			{
				SpectatorLocationLeft = SpectatorLocation_1;
				SpectatorLocationRight = SpectatorLocation_0;
			}
			else
			{
				SpectatorLocationLeft = SpectatorLocation_0;
				SpectatorLocationRight = SpectatorLocation_1;
			}

			// Get the distance between the characters
			SpectatorDistance = SpectatorLocationRight - SpectatorLocationLeft;
			// TODO:FIX assuming 0 is always on the left (can be assumed for now since they cant jump)
			CameraDestination = SpectatorLocationLeft + (0.5f * SpectatorDistance);
			//UE_LOG(LogTemp, Warning, TEXT("CameraDestination: %f"), CameraDestination.X);
		}
		else
		{
			// Only one character is set focus the camera on that character
			// Get the character that is set
			ACharacter* SingleSpectator;
			if (SpectatorCharacter_0)
			{
				SingleSpectator = SpectatorCharacter_0;
			}
			else
			{
				SingleSpectator = SpectatorCharacter_1;
			}

			// Set the camera destination to the location of the set spectator
			CameraDestination = SingleSpectator->GetActorLocation();
		}

		// Calculate the velocity to update movement
		FVector CameraLocation = GetActorLocation();
		float result = CameraLocation.Y - CameraDestination.Y;
		if (result == 0)
		{
			CameraLocation.Y = 0.0f;
		}
		else
		{
			CameraVelocity.Y = (result < 0) ? -1.0f : 1.0f;
		}
	}
}

void ASceneCamera::ZoomIn()
{
	bZoomingIn = true;
}
void ASceneCamera::ZoomOut()
{
	bZoomingIn = false;
}

