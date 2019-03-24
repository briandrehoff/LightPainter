// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Saving/PainterSaveGame.h"
#include "PaintingGameMode.h"
#include "Kismet/GameplayStatics.h"

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

	if (PaintBrushHandControllerClass)
	{
		LeftPaintBrushHandController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
		if (LeftPaintBrushHandController != nullptr)
		{
			LeftPaintBrushHandController->SetHand(EControllerHand::Left);
			LeftPaintBrushHandController->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}

		RightPaintBrushHandController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
		if (RightPaintBrushHandController != nullptr)
		{
			RightPaintBrushHandController->SetHand(EControllerHand::Right);
			RightPaintBrushHandController->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("RightTrigger", EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction("RightTrigger", EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);
	PlayerInputComponent->BindAction("Save", EInputEvent::IE_Pressed, this, &AVRPawn::Save);
}

void AVRPawn::Save()
{
	auto GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->Save();

	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}