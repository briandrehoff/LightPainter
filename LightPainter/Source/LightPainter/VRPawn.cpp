// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Saving/PainterSaveGame.h"

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

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("RightTrigger", EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction("RightTrigger", EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);
	PlayerInputComponent->BindAction("Save", EInputEvent::IE_Pressed, this, &AVRPawn::Save);
	PlayerInputComponent->BindAction("Load", EInputEvent::IE_Pressed, this, &AVRPawn::Load);
}

void AVRPawn::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	Painting->SetState("Hello World!");
	Painting->Save();
}

void AVRPawn::Load()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load();
	if (Painting)
	{
		UE_LOG(LogTemp, Warning, TEXT("Painting State %s"), *Painting->GetState());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not found"));
	}
}