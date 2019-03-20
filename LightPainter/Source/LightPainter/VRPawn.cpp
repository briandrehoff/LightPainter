// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"

AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>("VRRoot");
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(VRRoot);
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	if (HandControllerClass)
	{
		LeftHandController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
		if (LeftHandController != nullptr)
		{
			LeftHandController->SetHand(EControllerHand::Left);
			LeftHandController->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}

		RightHandController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
		if (RightHandController != nullptr)
		{
			RightHandController->SetHand(EControllerHand::Right);
			RightHandController->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

