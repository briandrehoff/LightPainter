// Fill out your copyright notice in the Description page of Project Settings.

#include "HandControllerBase.h"

AHandControllerBase::AHandControllerBase()
{
	PrimaryActorTick.bCanEverTick = false;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>("MotionController");
	SetRootComponent(MotionController);
	MotionController->SetShowDeviceModel(true);
}