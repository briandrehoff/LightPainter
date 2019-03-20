// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HandController.h"

#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	AVRPawn();

protected:
	virtual void BeginPlay() override;

private:
	// Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandController> HandControllerClass;

	//Components
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* VRRoot;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	
	// Reference
	UPROPERTY(EditAnywhere)
	AHandController* LeftHandController;
	UPROPERTY(EditAnywhere)
	AHandController* RightHandController;
};
