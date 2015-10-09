// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SceneCamera.generated.h"

UCLASS()
class POTM_API ASceneCamera : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	// Root component to attach things to
	UCapsuleComponent* Root;
	// Camera spring arm that represents the camera boom
	USpringArmComponent* CameraBoom;
	// The camera that keeps the spectator characters in view
	UCameraComponent* SceneCamera;

	// The camera will keep these two characters in view
	// The first character reference
	UPROPERTY(EditAnywhere, Category = "Spectators")
	ACharacter* SpectatorCharacter_0;
	// The second character reference
	UPROPERTY(EditAnywhere, Category = "Spectators")
	ACharacter* SpectatorCharacter_1;

	// The destination of the camera
	FVector CameraDestination;
	void UpdateCameraDestination();
	// The velocity of the camera movement
	FVector CameraVelocity;
	// The number of units used to offset move per 1 unit of tick time
	float CameraSpeed;
	
	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	void ZoomIn();
	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	void ZoomOut();

	float ZoomFactor;
	FVector SpectatorDistance;
	bool bZoomingIn;
};
