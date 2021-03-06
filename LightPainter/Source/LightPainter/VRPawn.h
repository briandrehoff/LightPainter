// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HandControllerBase.h"

#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	AVRPawn();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void RightTriggerPressed() { if (RightHandController) RightHandController->TriggerPressed(); }
	void RightTriggerReleased() { if (RightHandController) RightHandController->TriggerReleased(); }

	void PaginateRightAxisInput(float AxisValue);
	void UpdateCurrentPage(int32 Offset);

	// Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> RightHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
	float PaginationThumbstickThreshold = 0.9;

	// Components
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* VRRoot;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	
	// Reference
	UPROPERTY(VisibleAnywhere)
	AHandControllerBase* LeftHandController;
	UPROPERTY(VisibleAnywhere)
	AHandControllerBase* RightHandController;

	// State
	int32 LastPaginationOffset = 0;
};
