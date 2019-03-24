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
	void RightTriggerPressed() { if (RightPaintBrushHandController) RightPaintBrushHandController->TriggerPressed(); }
	void RightTriggerReleased() { if (RightPaintBrushHandController) RightPaintBrushHandController->TriggerReleased(); }

	void Save();

	// Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> PaintBrushHandControllerClass;

	//Components
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* VRRoot;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	
	// Reference
	UPROPERTY(VisibleAnywhere)
	AHandControllerBase* LeftPaintBrushHandController;
	UPROPERTY(VisibleAnywhere)
	AHandControllerBase* RightPaintBrushHandController;

	// State
	UPROPERTY()
	FString CurrentSlotName;
};
