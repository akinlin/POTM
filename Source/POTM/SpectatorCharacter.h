// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SpectatorCharacter.generated.h"

UCLASS()
class POTM_API ASpectatorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpectatorCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Spectator Movement")
	void JogStarted(float Direction);
	float JoggingDirection;
	UFUNCTION(BlueprintCallable, Category = "Spectator Movement")
	void JogStopped();
	bool bIsJogging;

	UFUNCTION(BlueprintCallable, Category = "Spectator Movement")
	void CrouchingStarted();
	UFUNCTION(BlueprintCallable, Category = "Spectator Movement")
	void CrouchingStopped();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spectator Movement")
	bool bIsCrouching;

	UFUNCTION(BlueprintCallable, Category = "Spectator Movement")
	void JumpingStarted();
	UFUNCTION(BlueprintCallable, Category = "Spectator Movement")
	void JumpingStopped();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spectator Movement")
	bool bIsJumping;

	// A camera attached to the character that is used for dramatic angles of the character
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* SpectatorCamera;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	UCameraComponent* GetSpectatorCamera() { return SpectatorCamera; };

	UPROPERTY(EditAnywhere, Category = "Spectator Text")
	UTextRenderComponent* SpectatorName;
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void DisplayName(bool isDisplayed);

	// Input function for Y axis (This direction is forward because the character is looking left and right)
	void MoveForward(float AxisValue);
	
};
