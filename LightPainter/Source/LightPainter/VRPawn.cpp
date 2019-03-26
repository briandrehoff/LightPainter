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

	if (LeftHandControllerClass)
	{
		LeftHandController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
		if (LeftHandController != nullptr)
		{
			LeftHandController->SetHand(EControllerHand::Left);
			LeftHandController->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}

	if (RightHandControllerClass)
	{

		RightHandController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
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
	PlayerInputComponent->BindAxis("PaginateRight", this, &AVRPawn::PaginateRightAxisInput);
}

void AVRPawn::PaginateRightAxisInput(float AxisValue)
{
	int32 PaginationOffset = 0;
	PaginationOffset += AxisValue > PaginationThumbstickThreshold ? 1 : 0;
	PaginationOffset += AxisValue < -PaginationThumbstickThreshold ? -1 : 0;
	
	if (PaginationOffset != LastPaginationOffset && PaginationOffset != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Paginate %d"), PaginationOffset);
	}

	LastPaginationOffset = PaginationOffset;
}